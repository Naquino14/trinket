#ifndef _TRINKETPARSER_H
#define _TRINKETPARSER_H

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

#pragma endregion Includes

#pragma region Trinketparser

/// @brief The maximum number of characters in a line of text on the lcd.
#define MAX_CHAR 16

/// @brief The maximum number of frames in a trinket animation.
#define MAX_FRAMES 120

#pragma region Structs

/// A frame of the trinket animation.
typedef struct trinket_frame_t {
    byte color[3];
    int time;
    char text_top[MAX_CHAR + 1];
    char text_bottom[MAX_CHAR + 1];
} trinket_frame;

/// The trinket configuration.
typedef struct trinket_conf_t {
    int default_time;
    int start_time;
    int restart_time;
    byte default_color[3];
    int num_frames;
    trinket_frame* frames;
} trinket_conf;

#pragma endregion Structs

#pragma region Functions

/// @brief Inserts a frame into the config
/// @param cf the config to insert the frame into
/// @param fr the fame to insert
/// @returns true if the operation was successful
bool trinket_insert_frame(trinket_conf* cf, trinket_frame fr);

/// @brief Parses a trinket configuration file.
/// @param f The text of the trinket configuration file.
/// @return The trinket configuration.
trinket_conf* trinket_parse(char* f);

/// @brief Frees a trinket configuration.
/// @param cf The trinket configuration to free.
void trinket_free_conf(trinket_conf* cf);

#pragma endregion Functions

#pragma endregion Trinketparser

#endif  // !_TRINKETPARSER_H
