#include <stdint.h>
#include <stdio.h>

#include "backlight.h"
#include "frames.h"
#include "lcd.h"
#include "pico/stdlib.h"
#include "trinket.h"
#include "trinketparser.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 0
#define I2C_SCL 1

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)       \
    (byte & 0x80 ? '1' : '0'),     \
        (byte & 0x40 ? '1' : '0'), \
        (byte & 0x20 ? '1' : '0'), \
        (byte & 0x10 ? '1' : '0'), \
        (byte & 0x08 ? '1' : '0'), \
        (byte & 0x04 ? '1' : '0'), \
        (byte & 0x02 ? '1' : '0'), \
        (byte & 0x01 ? '1' : '0')

void i2cinit(void) {
    i2c_init(I2C_PORT, 400 * 1000);
    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);
}

int main(void) {
    stdio_init_all();
    i2cinit();

    sleep_ms(6000);

    printf("Initializing LCD...\n");
    // printf("%s\n", FRAMES);
    lcd_init_def initdef = mkinitdef();
    initdef.display_switch = mkcmd(LCD_DISPLAY_SWITCH, 3, LCD_DISPLAY_SWITCH_DISP_ON, LCD_DISPLAY_SWITCH_BLINK_ON, LCD_DISPLAY_SWITCH_CUR_ON);
    setinitdef(&initdef);
    printf("Initializing LCD...\n");
    lcd_init(I2C_PORT, I2C_SDA, I2C_SCL);
    printf("LCD initialized\n");
    printf("Initializing backlight...\n");
    backlight_init(I2C_PORT, I2C_SDA, I2C_SCL);
    printf("Backlight initialized\n");

    // parse config
    printf("Reading config...\n");
    char frames[FRAMES_LEN + 1];
    strncpy(frames, FRAMES, FRAMES_LEN + 1);
    frames[FRAMES_LEN] = '\0';
    trinket_conf* cf = trinket_parse(frames);
    printf("Config Read!\n");
    printf(
        "Config:\nDefault color: #%.2x%.2x%.2x\n"
        "Default time: %dms\nStart time: %dms\nRestart time: %dms\nFrames: %d\n",
        cf->default_color[0], cf->default_color[1], cf->default_color[2],
        cf->default_time, cf->start_time, cf->restart_time, cf->num_frames);
    fflush(stdout);
    for (int i = 0; i < cf->num_frames; i++) {
        printf(
            "Frame %d:\n\tColor: #%.2x%.2x%.2x\n\t"
            "Time: %dms\n\tText top: %s\n\tText bottom: %s\n",
            i + 1,
            (cf->frames + i)->color[0],
            (cf->frames + i)->color[1],
            (cf->frames + i)->color[2],
            (cf->frames + i)->time, (cf->frames + i)->text_top, (cf->frames + i)->text_bottom);
    }
    printf("bruh\n");

    // Main loop
    sleep_ms(cf->start_time);
    for (;;) {
        printf("LOOP! NF:%d\n", cf->num_frames);
        for (int i = 0; i < cf->num_frames; i++) {
            writecmd(LCD_SCREEN_CLEAR);
            sleep_ms(10);
            trinket_frame* fr = &cf->frames[i];
            printf("Frame %d: %dms #%.2x%.2x%.2x: |%s|%s|\n", i, fr->time, fr->color[0], fr->color[1], fr->color[2], fr->text_top, fr->text_bottom);
            set_text(fr->text_top, 0);
            set_text(fr->text_top, 1);
            backlight_set_color(fr->color[0], fr->color[1], fr->color[2]);
            sleep_ms(fr->time);
        }
        sleep_ms(cf->restart_time);
    }
    trinket_free_conf(cf);
    backlight_set_color(0x11, 0, 0);
    set_text("freed!", 0);
    return 0;
}
