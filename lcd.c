// See JHD1313 datasheet
// Author: Nate Aquino (naquino14@outlook.com)

#include "lcd.h"

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

static uint _baudrate = 400000U;

static lcd_init_def _initdef = {
    .func_set = LCD_FUNCTION_SET | LCD_FUNCTION_SET_8BIT | LCD_FUNCTION_SET_2LINE | 0x4,
    .display_switch = LCD_DISPLAY_SWITCH | LCD_DISPLAY_SWITCH_DISP_ON | LCD_DISPLAY_SWITCH_CUR_ON | LCD_DISPLAY_SWITCH_BLINK_ON,
    .entry_mode_set = LCD_ENTRY_MODE_SET | LCD_ENTRY_MODE_INC};

#pragma region Public Methods

void setbaudrate(uint baudrate) {
    _baudrate = baudrate;
}

void lcd_init(i2c_inst_t* i2cport, uint sdaport, uint sclport) {
    // wait at least 30 ms for LCD to power up
    sleep_ms(50);

    // function set
    writecmd(_initdef.func_set);
    sleep_ms(5);  // wait at least 4.1 ms

    writecmd(_initdef.func_set);
    sleep_us(150);

    writecmd(_initdef.func_set);
    sleep_us(150);

    writecmd(_initdef.func_set);
    sleep_us(150);

    // display on/off control
    writecmd(_initdef.display_switch);
    sleep_ms(2);

    // clear display
    writecmd(LCD_SCREEN_CLEAR);
    sleep_ms(2);

    // entry mode set
    writecmd(_initdef.entry_mode_set);
    sleep_ms(2);

    // initialization end
    printf("LCD initialized\n");
}

#pragma endregion

#pragma region Helper Methods

int writecmd(byte cmd) {
    const byte _cmd[2] = {0x80, cmd};
    return i2c_write_blocking(i2c0, LCD_ADDR, _cmd, 2, false);
}

int set_text(char* text, int line) {
    return 0;  // not implemented
}

byte mkcmd(byte cmd, int n_flags, ...) {
    va_list args;
    va_start(args, n_flags);
    for (int i = 0; i < n_flags; i++)
        cmd |= va_arg(args, uint);
    return cmd;
}

lcd_init_def mkinitdef() {
    lcd_init_def def;
    def.func_set = mkcmd(
        LCD_FUNCTION_SET, 3,
        LCD_FUNCTION_SET_8BIT,
        LCD_FUNCTION_SET_2LINE,
        0x4);
    def.display_switch = mkcmd(
        LCD_DISPLAY_SWITCH, 3,
        LCD_DISPLAY_SWITCH_DISP_ON,
        LCD_DISPLAY_SWITCH_CUR_ON,
        LCD_DISPLAY_SWITCH_BLINK_ON);
    def.entry_mode_set = LCD_ENTRY_MODE_SET;
    return def;
}

void setinitdef(lcd_init_def* def) {
    _initdef = *def;
}

#pragma endregion