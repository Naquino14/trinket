#include "trinketparser.h"

#pragma region Helper Functions

/// @brief Initializes a config
/// @returns A pointer to the config in memory
static trinket_conf* trinket_make_config(void) {
    trinket_conf* cf = malloc(sizeof(trinket_conf));
    cf->default_time = 0;
    cf->start_time = 0;
    cf->restart_time = 0;
    cf->default_color[0] = 0xFF;
    cf->default_color[1] = 0xFF;
    cf->default_color[2] = 0xFF;
    cf->num_frames = 0;

    cf->frames = malloc(sizeof(trinket_frame) * MAX_FRAMES);
    return cf;
}

/// @brief Reads a hex string into an array of uint8_t of size n
/// @param s The hex string to read
/// @param buf The buffer to read the bytes into
/// @param n The number of hex numbers to read
static void hstrtob(char* s, byte* buf, unsigned int n) {
    char hexstr[2];
    for (unsigned int i = 0; i < n; i++) {
        hexstr[0] = *s++;
        hexstr[1] = *s++;
        buf[i] = (byte)strtol(hexstr, NULL, 16);
    }
}

#pragma endregion Helper Functions

#pragma region Functions

bool trinket_insert_frame(trinket_conf* cf, trinket_frame fr) {
    if (cf->num_frames > MAX_FRAMES)
        return 0;
    cf->frames[cf->num_frames++] = fr;
    return 1;
}

trinket_conf* trinket_parse(char* f) {
    trinket_conf* cf = trinket_make_config();
    // default hex
    if (*f != ';') {
        hstrtob(f, cf->default_color, 3);  // first 6 bytes are hex
        f += 6;
    }
    f++;  // skip semi
    // change newline to null
    char* off = strchr(f, '\n');
    *off = '\0';
    sscanf(f, "%d;%d;%d;", &cf->default_time, &cf->start_time, &cf->restart_time);
    f += (strrchr(f, ';') - f) + 1;  // jump over semi
    *off = '\n';
    while ((f = strchr(f, '\n')) != NULL) {
        f++;
        trinket_frame fr = {.time = 0};
        if (*f != ';') {  // hex parse
            hstrtob(f, fr.color, 3);
            f += 6;
        } else {
            fr.color[0] = cf->default_color[0];
            fr.color[1] = cf->default_color[1];
            fr.color[2] = cf->default_color[2];
        }
        f++;              // skip semi
        if (*f != ';') {  // time parse
            off = strchr(f, ';');
            *off = '\0';
            fr.time = (int)strtol(f, NULL, 10);
            fr.time = fr.time < 0 ? fr.time * -1 : fr.time;
            f += (off - f) + 1;
        } else {
            fr.time = cf->default_time;
            f++;
        }
        if (*f != ';') {  // first string
            off = strchr(f, ';');
            *off = '\0';
            strncpy(fr.text_top, f, MAX_CHAR);
            f += (off - f) + 1;
        } else
            f++;
        if (*f != ';') {  // second string
            off = strchr(f, ';');
            *off = '\0';
            strncpy(fr.text_bottom, f, MAX_CHAR);
            f += (off - f) + 1;
        } else
            f++;
        trinket_insert_frame(cf, fr);
    }
    return cf;
}

void trinket_free_conf(trinket_conf* cf) {
    free(cf->frames);
    free(cf);
}

#pragma endregion Functions