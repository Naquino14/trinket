// Author: Nate Aquino (naquino14@outlook.com)

#ifndef _TRINKET_H
#define _TRINKET_H

#ifndef byte
#define byte uint8_t
#endif  // !byte

#pragma region Includes

#ifndef _STDINT_H
#include <stdint.h>
#endif  // !_STDINT_H

#ifndef _STDLIB_H
#include <stdlib.h>
#endif  // !_STDLIB_H

#ifndef _STDIO_H
#include <stdio.h>
#endif  // !_STDIO_H

#ifndef _STRING_H
#include <string.h>
#endif  // !_STRING_H

#ifndef _STDBOOL_H
#include <stdbool.h>
#endif  // !_STDBOOL_H

#ifndef _STDARG_H
#include <stdarg.h>
#endif  // !_STDARG_H

#ifndef _PICO_STDLIB_H
#include "pico/stdlib.h"
#endif  // !PICO_STDLIB_H

#include "backlight.h"
#include "frames.h"
#include "lcd.h"
#include "trinketparser.h"

#pragma endregion Includes

#pragma region Trinket

#pragma region Functions

/// @brief Initializes LCD and Backlight
/// @param i2cport The I2C port to use.
/// @param sdaport The SDA port to use.
/// @param sclport The SCL port to use.
void trinket_init_all(i2c_inst_t* i2cport, uint sdaport, uint sclport);

/// @brief Loads the pico frames from
void trinket_load_config();

/// @brief Reads a config and displays it
void trinket_start();

/// @brief Frees all resources related to trinket
void trinket_free();

/// @brief @brief Prints the current config to stdout
void trinket_print_config();

#pragma endregion Functions

#pragma endregion Trinket

#endif  // !_TRINKET_H