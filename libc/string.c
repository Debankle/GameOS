#include "string.h"

int strlen(const char *s) {
    int l;
    for (l = 0; s[l] != '\0'; l++);
    return l;
}
