// see PCA9633 datasheet
// Author: Nate Aquino

#ifndef _BACKLIGHT_H
#define _BACKLIGHT_H

#ifndef byte
#define byte uint8_t
#endif  // !byte

#pragma region Includes

#include <stdint.h>
#include <stdio.h>

#include "hardware/i2c.h"

#pragma endregion Includes

#pragma region Backlight

#define BACKLIGHT_ADDR 0x62
#define BACKLIGHT_ADDR_V5 0x30
#define BACKLIGHT_ADDR_RST 0x03

#pragma region Registers

/// Mode register 1
#define MODE1 0x00

/// Mode register 2
#define MODE2 0x01

/// Brightness control LED0
#define PWM0 0x02

/// Brightness control LED1
#define PWM1 0x03

/// Brightness control LED2
#define PWM2 0x04

/// Brightness control LED3
#define PWM3 0x05

/// Group duty cycle control
#define GRPPWM 0x06

/// Group frequency
#define GRPFREQ 0x07

/// LED output state
#define LEDOUT 0x08

/// I2C-bus subaddress 1
#define SUBADR1 0x09

/// I2C-bus subaddress 2
#define SUBADR2 0x0A

/// I2C-bus subaddress 3
#define SUBADR3 0x0B

/// All-call I2C-bus address
#define ALLCALLADR 0x0C

/// Red LED register
#define REG_RED 0x4

/// Green LED register
#define REG_GREEN 0x3

/// Blue LED register
#define REG_BLUE 0x2

/// v5 Red LED register
#define REG_RED_V5 0x6

/// v5 Green LED register
#define REG_GREEN_V5 0x7

/// v5 Blue LED register
#define REG_BLUE_V5 0x8

#pragma endregion Registers

#pragma region Register flags

// Mode 1 register flags

#define MODE1_DEFAULT 0x91

/// Sleep mode on. Disables the oscillator and turns on low power mode.
#define MODE1_SLEEP_ON 0x10

/// Sleep mode off. Enables the oscillator.
#define MODE1_SLEEP_OFF 0x0

/// Device responds to LED subaddress 1.
#define MODE1_SUB1_ON 0x08

/// Device does not respond to LED subaddress 1.
#define MODE1_SUB1_OFF 0x0

/// Device responds to LED subaddress 2.
#define MODE1_SUB2_ON 0x04

/// Device does not respond to LED subaddress 2.
#define MODE1_SUB2_OFF 0x0

/// Device responds to LED subaddress 3.
#define MODE1_SUB3_ON 0x02

/// Device does not respond to LED subaddress 3.
#define MODE1_SUB3_OFF 0x0

/// Device responds to all-call I2C-bus address.
#define MODE1_ALLCALL_ON 0x01

/// Device does not respond to all-call I2C-bus address.
#define MODE1_ALLCALL_OFF 0x0

// Mode 2 register flags

#define MODE2_DMBLNK_ON 0x20

#define MODE2_DMBLNK_OFF 0x0

#define MODE2_INVRT_ON 0x10

#define MODE2_INVRT_OFF 0x0

#define MODE2_OCH_ON 0x08

#define MODE2_OCH_OFF 0x0

#define MODE2_OUTDRV_ON 0x04

#define MODE2_OUTDRV_OFF 0x0

#pragma endregion Register flags

#pragma region reset magic

#define BACKLIGHT_RESET_MAGIC1 0xA5
#define BACKLIGHT_RESET_MAGIC2 0x5A

#pragma endregion reset magic

#pragma region Methods

/// @brief Initializes the backlight I2C device.
/// @param i2cport The I2C port to use.
/// @param sdaport The SDA port to use.
/// @param sclport The SCL port to use.
void backlight_init(i2c_inst_t* i2cport, uint sdaport, uint sclport);

/// @brief Sets the backlight color.
/// @param red The red value.
/// @param green The green value.
void backlight_set_color(byte red, byte green, byte blue);

#pragma endregion Methods

#pragma endregion Backlight

#endif  // !_BACKLIGHT_H
