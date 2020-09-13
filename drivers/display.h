#ifndef GAMEOS_DISPLAY_H
#define GAMEOS_DISPLAY_H

#define MAX_ROWS 25
#define MAX_COLS 80

typedef enum colour {
    BLACK,
    BLUE,
    GREEN,
    CYAN,
    RED,
    MAGENTA,
    BROWN,
    LIGHT_GREY,
    DARK_GREY,
    LIGHT_BLUE,
    LIGHT_GREEN,
    LIGHT_CYAN,
    LIGHT_RED,
    LIGHT_MAGENTA,
    LIGHT_BROWN,
    WHITE
} colour_t;

void kprint(const char *s);
void display_init();
void clear_display();

#endif // GAMEOS_DISPLAY_H