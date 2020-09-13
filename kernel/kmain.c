#include "../drivers/display.h"

void kmain() {
    display_init();
    kprint("Hello World!\n");
}