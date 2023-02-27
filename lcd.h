// See JHD1313 datasheet
// Author: Nate Aquino (naquino14@outlook.com)

#ifndef _RGB_LCD_H
#define _RGB_LED_H

#ifndef byte
#define byte uint8_t
#endif  // !byte

#pragma region Includes

#ifndef _STDINT_H
#include <stdint.h>
#endif  // !_STDINT_H

#ifndef _STDIO_H
#include <stdio.h>
#endif  // !_STDIO_H

#ifndef _HARDWARE_I2C_H
#include "hardware/i2c.h"
#endif  // !_HARDWARE_I2C_H

#ifndef _PICO_STDIO_H
#include "pico/stdlib.h"
#endif  // !_PICO_STDIO_H

#ifndef _STDARG_H
#include <stdarg.h>
#endif  // !_STDARG_H

#pragma endregion Includes

#pragma region LCD

/// The address of the LCD I2C device.
#define LCD_ADDR (0x7C >> 1)

#pragma region LCD commands

/// Clears the screen, sets the address counter to 0
/// and returns the cursor to the start.
#define LCD_SCREEN_CLEAR 0x1
/// Sets Digital Display RAM address to 0,
/// and returns the cursor to the beginning.
/// Doesnt clear display.
#define LCD_CURSOR_RETURN 0x2
/// Sets Digital Display RAM address to 0,
/// returns the cursor to the beginning, but leaves
/// the content on the LCD unchanged.
#define LCD_ENTRY_MODE_SET 0x4
/// Sets the display on/off,
/// sets the cursor on/off,
/// and sets blink on/off.
#define LCD_DISPLAY_SWITCH 0x8
/// Moves the cursor/whole display,
/// leaving the Digigal Display RAM unchanged.
#define LCD_SHIFT_CURSOR 0x10
/// Sets the display bit mode,
/// wether or not we use 1/2 display lines
/// and the font type to 5x10/5x7.
#define LCD_FUNCTION_SET 0x20
/// Set the Character Generator RAM address
/// and prepares it to recieve data.
#define LCD_SET_CGRAM_ADDR 0x40
/// Set the Digital Display RAM address
/// and prepares it to recieve data.
#define LCD_SET_DDRAM_ADDR 0x80

#pragma endregion LCD commands

#pragma region LCD flags

// Entry mode Set flags

/// Sets the entry moving direction of the cursor
/// to the right.
#define LCD_ENTRY_MODE_INC 0x2
/// Sets the entry moving direction of the cursor.
/// to the left.
#define LCD_ENTRY_MODE_DEC 0x0
/// Sets the entry shift to incriment.
#define LCD_ENTRY_MODE_SHIFT 0X1
// Sets the entry shift to decriment.
#define LCD_ENTRY_MODE_NSHFT 0x0

// Display Switch flags

/// Turn the LCD display on.
#define LCD_DISPLAY_SWITCH_DISP_ON 0x4
/// Turn the LCD display off.
#define LCD_DISPLAY_SWITCH_DISP_OFF 0x0
/// Turn the LCD cursor on.
#define LCD_DISPLAY_SWITCH_CUR_ON 0x2
/// Turn the LCD cursor off.
#define LCD_DISPLAY_SWITCH_CUR_OFF 0x0
/// Turn the LCD cursor blink on.
#define LCD_DISPLAY_SWITCH_BLINK_ON 0x1
/// Turn the LCD cursor blink off.
#define LCD_DISPLAY_SWITCH_BLINK_OFF 0x0

// Shift Cursor flags

/// Shifts the cursor when incrimenting or decrimenting.
#define LCD_SHIFT_CURSOR_DISP_SHIFT 0x8
/// Shifts the display when incrimenting or decrimenting.
#define LCD_SHIFT_CURSOR_CURS_SHIFT 0x0
/// Increments the cursor position.
#define LCD_SHIFT_CURSOR_RIGHT 0x4
/// Decrements the cursor position.
#define LCD_SHIFT_CURSOR_LEFT 0x0

// Function Set flags

/// Sets the LCD to 8 bit mode.
#define LCD_FUNCTION_SET_8BIT 0x10
/// Sets the LCD to 4 bit mode.
#define LCD_FUNCTION_SET_4BIT 0x0
/// Sets the LCD to use 2 display lines.
#define LCD_FUNCTION_SET_2LINE 0x8
/// Sets the LCD to use 1 display line.
#define LCD_FUNCTION_SET_1LINE 0x0
/// Sets the LCD to use 5x10 font.
#define LCD_FUNCTION_SET_5X10 0x4
/// Sets the LCD to use 5x7 font.
#define LCD_FUNCTION_SET_5X7 0x0

#pragma endregion LCD flags

#pragma region Structs

/// @brief A struct containing the default initialization commands for the LCD.
typedef struct lcd_init_def_t {
    byte func_set;
    byte display_switch;
    byte entry_mode_set;
} lcd_init_def;

#pragma endregion Structs

#pragma region Methods

/// @brief Initializes the LCD and the backlight I2C devices.
/// @param i2cport The I2C port to use.
/// @param sdaport The SDA port to use.
/// @param sclport The SCL port to use.
void lcd_init(i2c_inst_t* i2cport, uint sdaport, uint sclport);

/// @brief sets the baudrate of the I2C port. (By default 400kHz)
/// @param baudrate Baudrate. (in Hz)
void setbaudrate(uint baudrate);

/// @brief Combines flags of a command into a single byte. TODO: mark as static when done testing.
/// @param cmd The command to combine flags with.
/// @param n_flags The number of flags to combine.
/// @param ... The flags to combine.
/// @return The combined flags.
byte mkcmd(byte cmd, int n_flags, ...);

/// @brief Makes an lcd initialization defaults struct.
/// @return The lcd initialization defaults struct.
lcd_init_def mkinitdef();

/// @brief Sets the initialization defaults for the LCD.
/// @param def The initialization defaults struct.
void setinitdef(lcd_init_def* def);

/// @brief Sends a command to the LCD.
/// @param cmd The command to send.
/// @returns The number of bytes sent or -2 if the send failed.
int writecmd(byte cmd);

/// @brief Sets the text of a line on the LCD.
/// @param text The text to set.
/// @param line The line to set the text on.
/// @returns The number of bytes sent or -2 if the send failed.
int set_text(char* text, int line);

#pragma endregion Methods

#pragma endregion LCD

#endif  // !RGB_LCD_H
