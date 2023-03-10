#include <stdint.h>
#include <stdio.h>

#include "backlight.h"
#include "lcd.h"
#include "pico/stdlib.h"

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

    printf("Initializing LCD...\n");
    lcd_init_def initdef = mkinitdef();
    initdef.display_switch = mkcmd(LCD_DISPLAY_SWITCH, 3, LCD_DISPLAY_SWITCH_DISP_ON, LCD_DISPLAY_SWITCH_BLINK_ON, LCD_DISPLAY_SWITCH_CUR_ON);
    setinitdef(&initdef);
    printf("Initializing LCD...\n");
    lcd_init(I2C_PORT, I2C_SDA, I2C_SCL);
    printf("LCD initialized\n");
    printf("Initializing backlight...\n");
    backlight_init(I2C_PORT, I2C_SDA, I2C_SCL);
    printf("Backlight initialized\n");
    set_text("Chom", 0);

    // cycle through rgb colors
    for (;;) {
        backlight_set_color(50, 0, 0);
        sleep_ms(500);
        backlight_set_color(0, 50, 0);
        sleep_ms(500);
        backlight_set_color(0, 0, 50);
        sleep_ms(500);
    }
    return 0;
}
