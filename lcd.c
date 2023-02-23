// See JHD1313 datasheet
// Author: Nate Aquino (naquino14@outlook.com)

#include "lcd.h"

#include <stdint.h>
#include <stdio.h>

#include "hardware/i2c.h"
#include "pico/stdlib.h"

#pragma region Private Methods

void init() {
    for (;;) {
        printf("Initializing LCD...\r\n");
        sleep_ms(1000);
    }
}

#pragma endregion