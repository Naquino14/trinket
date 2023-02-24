// See JHD1313 datasheet
// Author: Nate Aquino (naquino14@outlook.com)

#include "lcd.h"

struct lcd_init_def_t {
    byte func_set;
    byte display_switch;
    byte entry_mode_set;
};

static uint _baudrate = 400000U;

static lcd_init_def _initdef = {
    .func_set = LCD_FUNCTION_SET | LCD_FUNCTION_SET_8BIT | LCD_FUNCTION_SET_2LINE | 0x4,
    .display_switch = LCD_DISPLAY_SWITCH | LCD_DISPLAY_SWITCH_DISP_ON | LCD_DISPLAY_SWITCH_CUR_ON | LCD_DISPLAY_SWITCH_BLINK_ON,
    .entry_mode_set = LCD_ENTRY_MODE_SET};

#pragma region Public Methods

void setbaudrate(uint baudrate) {
    _baudrate = baudrate;
}

void lcd_init(i2c_inst_t* i2cport, uint sdaport, uint sclport) {
    i2c_init(i2cport, _baudrate);
    gpio_set_function(sdaport, GPIO_FUNC_I2C);
    gpio_set_function(sclport, GPIO_FUNC_I2C);
    gpio_pull_up(sdaport);
    gpio_pull_up(sclport);

    // wait at least 30 ms for LCD to power up
    sleep_ms(35);

    // function set based on the current startup conditions
    i2c_write_blocking(i2cport, LCD_ADDR, &_initdef.func_set, 1, false);

    // wait at least 39 μs
    sleep_us(100);

    // set display on/off control
    i2c_write_blocking(i2cport, LCD_ADDR, &_initdef.display_switch, 1, false);

    // wait at least 39 μs
    sleep_us(100);

    // clear display
    byte clear = LCD_SCREEN_CLEAR;
    i2c_write_blocking(i2cport, LCD_ADDR, &clear, 1, false);

    // wait at least 1.53 ms
    sleep_ms(4);

    // set entry mode
    i2c_write_blocking(i2cport, LCD_ADDR, &_initdef.entry_mode_set, 1, false);

    // initialization end
}

#pragma endregion

#pragma region Helper Methods

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