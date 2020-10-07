#include "../drivers/display.h"
#include "../drivers/serial.h"
#include "../cpu/gdt.h"

void kinit() {
    display_init();
    serial_init();
    gdt_init();
}

void kmain() {
    kinit();

    kprint("Hello World!\n");
    write_serial(SERIAL_COM1_BASE, 'p');
}