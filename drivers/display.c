#include "display.h"
#include "cursor.h"
#include "../libc/string.h"

char *video_addr;
int row;
int col;
int colour;

/* -------- PRIVATE FUNCTIONS -------- */

void kscroll() {
    col = 0;
    row = 0;
    for (int i = 0; i < MAX_ROWS; i++) {
        for (int j = 0; j < MAX_COLS; j++) {
            video_addr[2 * (int)(i * MAX_COLS + j)] = video_addr[2 * (int)((int)(i+1)*MAX_COLS+j)];
        }
    }
    col = 0;
    row = MAX_ROWS - 1;
}

void kprint_char(char c) {
    if (c == '\n') {
        col = 0;
        row++;
    }
    else {
        int pos = 80 * row + col;
        video_addr[2*pos] = c;
        video_addr[2*pos+1] = colour;
        col++;
        if (col == MAX_COLS) {
            col = 0;
            row++;
        }
    }

    if (row == MAX_ROWS) {
        kscroll();
    }
}

void set_colour(colour_t fg, colour_t bg) {
    colour = ((bg & 0x0f) << 4) | (fg & 0x0f);
}

/* -------- PUBLIC FUNCTIONS -------- */

void kprint(const char *s) {
    int len = strlen(s);
    for (int i = 0; i < len; i++) {
        kprint_char(s[i]);
    }
    move_cursor(row, col);
}

void clear_display() {
    row = 0;
    col = 0;
    for (int i =0; i < MAX_ROWS * MAX_COLS; i++) {
        kprint_char(' ');
    }
    row = 0;
    col = 0;
}

void display_init() {
    video_addr = (char *)0x000b8000;
    row = 0;
    col = 0;
    set_colour(WHITE, BLACK);
    clear_display();
}