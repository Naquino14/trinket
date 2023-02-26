#include <stdint.h>
#include <stdio.h>

#include "lcd.h"
#include "pico/stdlib.h"

// I2C defines
// This example will use I2C0 on GPIO8 (SDA) and GPIO9 (SCL) running at 400KHz.
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define I2C_PORT i2c0
#define I2C_SDA 0
#define I2C_SCL 1

int main(void) {
    stdio_init_all();
    sleep_ms(6000);

    printf("Initializing LCD...\n");
    lcd_init(I2C_PORT, I2C_SDA, I2C_SCL);
    for (;;) {
        printf("Looping\n");
        sleep_ms(1000);
    }
    return 0;
}
