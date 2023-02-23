// See JHD1313 datasheet
// Author: Nate Aquino (naquino14@outlook.com)

#ifndef RGB_LCD_H
#define RGB_LED_H

#pragma region LCD

/// The address of the LCD I2C device.
#define LCD_ADDR 0x7c >> 1

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
#define LCD_INPUT_SET 0x4
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

#pragma endregion

#pragma region LCD flags

// Input Set flags

/// Sets the entry moving direction of the cursor
/// to the right?
#define LCD_INPUT_SET_INC 0x2
/// Sets the entry moving direction of the cursor.
/// to the left?
#define LCD_INPUT_SET_DEC 0x0
/// Sets the entry shift to incriment.
#define LCD_INPUT_SET_SHIFT 0X1
// Sets the entry shift to decriment.
#define LCD_INPUT_SET_NSHFT 0x0

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

#pragma endregion

void init();

#endif  // !RGB_LCD_H
