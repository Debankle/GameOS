#include "serial.h"
#include "io.h"
#include "../libc/string.h"
#include "../libc/stdint.h"

void serial_configure_baud_rate(short com, short divisor) {
    outb(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    outb(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00ff);
    outb(SERIAL_DATA_PORT(com), divisor & 0x00ff);
}

void serial_configure_interrupt(short com) {
    outb(SERIAL_INTERRUPT_COMMAND_PORT(com), 0x00);
}

void serial_configure_line(short com) {
    outb(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffer(short com) {
    outb(SERIAL_FIFO_COMMAND_PORT(com), 0xc7);
}

void serial_configure_modem(short com) {
    outb(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}


int serial_is_transmit_fifo_empty(int com) {
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

int serial_is_data_recieved(int com) {
    return inb(SERIAL_LINE_STATUS_PORT(com)) & 1;
}


char read_serial(short com) {
    while (serial_is_data_recieved(com) == 0);
    return inb(SERIAL_DATA_PORT(com));
}

void write_serial(short com, char a) {
    while (serial_is_transmit_fifo_empty(com) == 0);
    outb(SERIAL_DATA_PORT(com), a);
}

void write_serial_str(short com, char *s) {
    uint32_t len = strlen(s);
    for (uint32_t i = 0; i < len; i++) {
        write_serial(com, s[i]);
    }
}

void init_serial_device(short com) {
    serial_configure_baud_rate(com, 0x03);
    serial_configure_interrupt(com);
    serial_configure_line(com);
    serial_configure_buffer(com);
    serial_configure_modem(com);
}

void serial_init() {
    init_serial_device(SERIAL_COM1_BASE);
    init_serial_device(SERIAL_COM2_BASE);
}