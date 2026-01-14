#include "backlight.h"

static byte _backlight_addr = 0x0;

static void checkaddr() {
    const byte cmd = 0x00;
    i2c_write_blocking(i2c0, BACKLIGHT_ADDR, &cmd, 0, true);

    byte out;
    int status = i2c_read_blocking(i2c0, BACKLIGHT_ADDR, &out, 1, false);
    if ((status != PICO_ERROR_GENERIC && status > 0) && out == MODE1_DEFAULT) {
        _backlight_addr = BACKLIGHT_ADDR;
        return;
    }
    sleep_us(200);
}

void backlight_reset(i2c_inst_t* i2cport) {
    byte cmd[2];

    // reset backlight
    cmd[0] = BACKLIGHT_RESET_MAGIC1;
    cmd[1] = BACKLIGHT_RESET_MAGIC2;
    i2c_write_blocking(i2cport, BACKLIGHT_ADDR_RST, cmd, 2, false);
    sleep_us(500);

    // turn on oscillator
    cmd[0] = MODE1;
    cmd[1] = MODE1_SLEEP_OFF;
    i2c_write_blocking(i2cport, _backlight_addr, cmd, 2, false);
    sleep_us(500);
}

void backlight_init(i2c_inst_t* i2cport, uint sdaport, uint sclport) {
    checkaddr();

    if (_backlight_addr == 0x0) {
        printf("Backlight not found\n");
        return;
    }

    // reset
    backlight_reset(i2cport);

    byte cmd[2];
    // init backlight

    // set MODE1 register to 0x0 to initialize the backlight
    cmd[0] = MODE1;
    cmd[1] = 0x0;
    i2c_write_blocking(i2cport, _backlight_addr, cmd, 2, false);
    sleep_us(200);

    // set OUTPUT register to work with PWM and GRPPWM
    cmd[0] = LEDOUT;
    cmd[1] = 0xFF;
    i2c_write_blocking(i2cport, _backlight_addr, cmd, 2, false);
    sleep_us(200);

    // set MODE2 register to enable DMBLNK
    cmd[0] = MODE2;
    cmd[1] = 0x20;
    i2c_write_blocking(i2cport, _backlight_addr, cmd, 2, false);
    sleep_us(200);

    // set backlight color to white
    backlight_set_color(0xFF, 0xFF, 0xFF);
}

void backlight_set_color(byte red, byte green, byte blue) {
    byte cmd[2];
    if (_backlight_addr == BACKLIGHT_ADDR_V5) {
        cmd[0] = REG_RED_V5;
        cmd[1] = red;
        i2c_write_blocking(i2c0, _backlight_addr, cmd, 2, false);
        cmd[0] = REG_GREEN_V5;
        cmd[1] = green;
        i2c_write_blocking(i2c0, _backlight_addr, cmd, 2, false);
        cmd[0] = REG_BLUE_V5;
        cmd[1] = blue;
        i2c_write_blocking(i2c0, _backlight_addr, cmd, 2, false);
    } else {
        cmd[0] = REG_RED;
        cmd[1] = red;
        i2c_write_blocking(i2c0, _backlight_addr, cmd, 2, false);
        cmd[0] = REG_GREEN;
        cmd[1] = green;
        i2c_write_blocking(i2c0, _backlight_addr, cmd, 2, false);
        cmd[0] = REG_BLUE;
        cmd[1] = blue;
        i2c_write_blocking(i2c0, _backlight_addr, cmd, 2, false);
    }
    sleep_us(200);
}
