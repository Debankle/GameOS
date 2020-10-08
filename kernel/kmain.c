#include "../drivers/display.h"
#include "../drivers/serial.h"
#include "../cpu/gdt.h"
#include "../cpu/idt.h"

void kinit() {
    serial_init();
    display_init();
    gdt_init();
    idt_init();
}

void kmain() {
    kinit();

    kprint("Hello World!\n");
}