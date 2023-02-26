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

struct lcd_init_def_t {
    byte func_set;
    byte display_switch;
    byte entry_mode_set;
};

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
    uint baud_a = i2c_init(i2cport, _baudrate);
    gpio_set_function(sdaport, GPIO_FUNC_I2C);
    gpio_set_function(sclport, GPIO_FUNC_I2C);
    gpio_pull_up(sdaport);
    gpio_pull_up(sclport);
    i2c_set_slave_mode(i2cport, false, LCD_ADDR);

    printf("initialized i2c with sda port %d and scl port %d | baud: %d\nWriting all commands to 0x%x : " BYTE_TO_BINARY_PATTERN "\n",
           sdaport,
           sclport,
           baud_a,
           LCD_ADDR,
           BYTE_TO_BINARY(LCD_ADDR));

    sleep_us(50000);

    byte cmd[2];
    cmd[0] = 0x80;
    cmd[1] = mkcmd(LCD_FUNCTION_SET, LCD_FUNCTION_SET_2LINE);
    printf("Writing function set: " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(cmd[1]));
    int result = i2c_write_blocking(i2cport, LCD_ADDR, &cmd, 2, false);
    printf("%s: %d\n", result > 0 ? "ACK" : "NACK", result);

    // wait at least 39 μs
    sleep_us(4500);

    printf("Writing function set again: " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(cmd[1]));
    result = i2c_write_blocking(i2cport, LCD_ADDR, &cmd, 2, false);
    printf("%s: %d\n", result > 0 ? "ACK" : "NACK", result);

    sleep_us(150);
    printf("Writing function set AGAIN: " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(cmd[1]));
    result = i2c_write_blocking(i2cport, LCD_ADDR, &cmd, 2, false);
    printf("%s: %d\n", result > 0 ? "ACK" : "NACK", result);

    printf("Writing function set AGAIN???: " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(cmd[1]));
    result = i2c_write_blocking(i2cport, LCD_ADDR, &cmd, 2, false);
    printf("%s: %d\n", result > 0 ? "ACK" : "NACK", result);

    // turn the display on
    cmd[1] = mkcmd(LCD_DISPLAY_SWITCH, 3, LCD_DISPLAY_SWITCH_DISP_ON, LCD_DISPLAY_SWITCH_CUR_ON, LCD_DISPLAY_SWITCH_BLINK_ON);
    printf("Writing display switch: " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(cmd[1]));
    result = i2c_write_blocking(i2cport, LCD_ADDR, &cmd, 2, false);
    printf("%s: %d\n", result > 0 ? "ACK" : "NACK", result);
    sleep_us(2000);

    // clear display
    cmd[1] = LCD_SCREEN_CLEAR;
    printf("Writing screen clear:" BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(cmd[1]));
    result = i2c_write_blocking(i2cport, LCD_ADDR, &cmd, 2, false);
    printf("%s: %d\n", result > 0 ? "ACK" : "NACK", result);
    sleep_us(2000);

    // initialize to default text direction (for romance languages)
    cmd[1] = mkcmd(LCD_ENTRY_MODE_SET, 2, LCD_ENTRY_MODE_DEC, 0x2);
    printf("Writing entry mode set: " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(cmd[1]));
    result = i2c_write_blocking(i2cport, LCD_ADDR, &cmd, 2, false);
    printf("%s: %d\n", result > 0 ? "ACK" : "NACK", result);

    // initialization end
    printf("LCD initialized\n");
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