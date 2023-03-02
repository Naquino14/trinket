#include "backlight.h"

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

static byte _backlight_addr = 0x0;

static void checkaddr() {
    printf("Checking for backlight at regular address 0x%02x\n", backlight_addr);
    const byte cmd = 0x00;
    i2c_write_blocking(i2c0, backlight_addr, &cmd, 0, true);

    printf("Reading from backlight at regular address 0x%02x\n", backlight_addr);
    byte out;
    int status = i2c_read_blocking(i2c0, backlight_addr, &out, 1, false);
    printf("Received " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(out));
    printf("%s: %d\n", status > 0 ? "ACK" : "NACK", status);
    if ((status != PICO_ERROR_GENERIC && status > 0) && out == MODE1_DEFAULT) {
        _backlight_addr = backlight_addr;
        return;
    } else
        printf("Backlight not found at regular address 0x%02x\n", backlight_addr);

    sleep_us(200);
}

void backlight_init(i2c_inst_t* i2cport, uint sdaport, uint sclport) {
    checkaddr();

    if (_backlight_addr == 0x0) {
        printf("Backlight not found\n");
        return;
    }
    byte cmd[2];
    int r = 0;
    // init backlight
    printf("Initializing backlight...\n");
    printf("Backlight found at address 0x%02x\n", _backlight_addr);

    // set MODE1 register to 0x0 to initialize the backlight
    cmd[0] = MODE1;
    cmd[1] = 0x0;
    printf("Sending command " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(cmd[0]), BYTE_TO_BINARY(cmd[1]));
    r = i2c_write_blocking(i2cport, _backlight_addr, cmd, 2, false);
    printf("%s: %d\n", r > 0 ? "ACK" : "NACK", r);
    sleep_us(200);

    // set OUTPUT register to work with PWM and GRPPWM
    cmd[0] = LEDOUT;
    cmd[1] = 0xFF;
    printf("Sending command " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(cmd[0]), BYTE_TO_BINARY(cmd[1]));
    r = i2c_write_blocking(i2cport, _backlight_addr, cmd, 2, false);
    printf("%s: %d\n", r > 0 ? "ACK" : "NACK", r);
    sleep_us(200);

    // set MODE2 register to enable DMBLNK
    cmd[0] = MODE2;
    cmd[1] = 0x20;
    printf("Sending command " BYTE_TO_BINARY_PATTERN " " BYTE_TO_BINARY_PATTERN "\n", BYTE_TO_BINARY(cmd[0]), BYTE_TO_BINARY(cmd[1]));
    r = i2c_write_blocking(i2cport, _backlight_addr, cmd, 2, false);
    printf("%s: %d\n", r > 0 ? "ACK" : "NACK", r);
    sleep_us(200);

    // set backlight color to white
    backlight_set_color(0xFF, 0xFF, 0xFF);
}

void backlight_set_color(byte red, byte green, byte blue) {
    byte cmd[2];
    if (_backlight_addr == backlight_addr_v5) {
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
