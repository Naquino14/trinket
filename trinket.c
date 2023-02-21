#include <stdint.h>
#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 1
#define I2C_SCL 2

enum lcd_cmd {
    SCREEN_CLEAR = 0x1,
    CURSOR_RETURN = 0x2,
    INPUT_SET = 0x4,
    INPUT_SET_INCR = 0x6,
    INPUT_SET_APP = 0x5,
    DISP_SW = 0x8,
    DISP_SW_DISP_ON = 0xC,
    DISP_SW_CURSOR_ON = 0xA,
    DISP_SW_BLINK_ON = 0x9,
    SHIFT = 0x10,
    SHIFT_DISPLAY = 0x18,
    SHIFT_RIGHT = 0x14,
    FUNC_SET = 0x20,
    FUNC_SET_8BIT = 0x30,
    FUNC_SET_2LINE = 0x28,
    FUNC_SET_FONT_5X10 = 0x24,
    CGRAM_AD_SET = 0x40,
    DDRAM_AD_SET = 0x80
};

int main() {
    stdio_init_all();

    // I2C Initialisation. Using it at 400Khz.
    i2c_init(I2C_PORT, 400 * 1000);

    gpio_set_function(I2C_SDA, GPIO_FUNC_I2C);
    gpio_set_function(I2C_SCL, GPIO_FUNC_I2C);
    gpio_pull_up(I2C_SDA);
    gpio_pull_up(I2C_SCL);

    puts("Hello, world!");

    return 0;
}
