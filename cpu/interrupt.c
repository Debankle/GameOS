#include "interrupt.h"
#include "../drivers/serial.h"
#include "../libc/string.h"

void interrupt_handler(registers_t regs) {
    write_serial_str(SERIAL_COM1_BASE, "recieved interrupt: ");
    char buffer[100];    
    write_serial_str(SERIAL_COM1_BASE, itoa((int)regs.int_no, buffer, 10));
    write_serial(SERIAL_COM1_BASE, '\n');
}