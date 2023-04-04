#include <stdint.h>
#include <stdio.h>

#include "frames.h"
#include "pico/stdlib.h"
#include "trinket.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 0
#define I2C_SCL 1

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

    trinket_init_all(I2C_PORT, I2C_SDA, I2C_SCL);

    trinket_load_config();
    trinket_print_config();

    trinket_start();

    trinket_free();
    backlight_set_color(0x11, 0, 0);
    set_text("freed!", 0);
    return 0;
}
