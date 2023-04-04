#include "trinket.h"

#pragma region Functions

/// @brief Trinket's config address
static trinket_conf* cf;

void trinket_init_all(i2c_inst_t* i2cport, uint sdaport, uint sclport) {
    lcd_init_def initdef = mkinitdef();
    initdef.display_switch = mkcmd(LCD_DISPLAY_SWITCH, 3, LCD_DISPLAY_SWITCH_DISP_ON, LCD_DISPLAY_SWITCH_BLINK_ON, LCD_DISPLAY_SWITCH_CUR_ON);
    setinitdef(&initdef);

    lcd_init(i2cport, sdaport, sclport);

    backlight_init(i2cport, sdaport, sclport);
}

void trinket_load_config() {
    // parse config
    char frames[FRAMES_LEN + 1];
    strncpy(frames, FRAMES, FRAMES_LEN + 1);
    frames[FRAMES_LEN] = '\0';
    cf = trinket_parse(frames);
}

void trinket_start() {
    // Main loop
    sleep_ms(cf->start_time);
    for (;;) {
        for (int i = 0; i < cf->num_frames; i++) {
            writecmd(LCD_SCREEN_CLEAR);
            sleep_ms(10);
            trinket_frame* fr = &cf->frames[i];

            set_text(fr->text_top, 0);
            set_text(fr->text_bottom, 1);
            backlight_set_color(fr->color[0], fr->color[1], fr->color[2]);
            sleep_ms(fr->time);
        }
        sleep_ms(cf->restart_time);
    }
}

void trinket_print_config() {
    if (cf == NULL) {
        printf("Config does not exist\n");
        return;
    }
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
}

void trinket_free() {
    trinket_free_conf(cf);
}

#pragma endregion Functions