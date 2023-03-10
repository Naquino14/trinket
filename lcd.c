// See JHD1313 datasheet
// Author: Nate Aquino (naquino14@outlook.com)

#include "lcd.h"

static uint _baudrate = 400000U;
static bool _2line = false;

static lcd_init_def _initdef = {
    .func_set = LCD_FUNCTION_SET | LCD_FUNCTION_SET_8BIT | LCD_FUNCTION_SET_2LINE | 0x4,
    .display_switch = LCD_DISPLAY_SWITCH | LCD_DISPLAY_SWITCH_DISP_ON | LCD_DISPLAY_SWITCH_CUR_ON | LCD_DISPLAY_SWITCH_BLINK_ON,
    .entry_mode_set = LCD_ENTRY_MODE_SET | LCD_ENTRY_MODE_INC};

#pragma region Public Methods

void setbaudrate(uint baudrate) {
    _baudrate = baudrate;
}

void lcd_init(i2c_inst_t* i2cport, uint sdaport, uint sclport) {
    _2line = _initdef.func_set & LCD_FUNCTION_SET_2LINE;

    // wait at least 30 ms for LCD to power up
    sleep_ms(35);

    // function set
    writecmd(_initdef.func_set);
    sleep_ms(5);  // wait at least 4.1 ms

    writecmd(_initdef.func_set);
    sleep_us(FAST_DELAY);

    writecmd(_initdef.func_set);
    sleep_us(FAST_DELAY);

    writecmd(_initdef.func_set);
    sleep_us(FAST_DELAY);

    // display on/off control
    writecmd(_initdef.display_switch);
    sleep_us(SLOW_DELAY);

    // clear display
    writecmd(LCD_SCREEN_CLEAR);
    sleep_us(SLOW_DELAY);

    // entry mode set
    writecmd(_initdef.entry_mode_set);
    sleep_us(SLOW_DELAY);
}

#pragma endregion

#pragma region Helper Methods

int writecmd(byte cmd) {
    const byte _cmd[2] = {0x80, cmd};
    return i2c_write_blocking(i2c0, LCD_ADDR, _cmd, 2, false);
}

void set_cursor(int pos, int line) {
    pos = (line == 0 ? pos | 0x80 : pos | 0xc0);
    byte data[2] = {0x80, pos};
    i2c_write_blocking(i2c0, LCD_ADDR, data, 2, false);
    sleep_us(FAST_DELAY);
}

int writedata(byte data) {
    const byte _data[2] = {0x40, data};
    return i2c_write_blocking(i2c0, LCD_ADDR, _data, 2, false);
}

void set_text(const char* text, int line) {
    int i = 0;
    set_cursor(0, line);
    while (text[i] != '\0') {
        set_cursor(i, line);
        writedata(text[i]);
        sleep_us(FAST_DELAY);
        i++;
    }
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
    def.entry_mode_set = mkcmd(LCD_ENTRY_MODE_SET, 2, LCD_ENTRY_MODE_INC, LCD_ENTRY_MODE_SHIFT);
    return def;
}

void setinitdef(lcd_init_def* def) {
    _initdef = *def;
}

#pragma endregion