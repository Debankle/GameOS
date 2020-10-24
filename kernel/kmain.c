#include "../drivers/display.h"
#include "../drivers/serial.h"
#include "../cpu/gdt.h"

void kinit() {
    serial_init();
    display_init();
    gdt_init();
}

void kmain() {
    kinit();

    kprint("Hello World!\n");
    write_serial_str(SERIAL_COM1_BASE, "Hello Serial\n");
}