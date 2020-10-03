#ifndef GAMEOS_SERIAL_H
#define GAMEOS_SERIAL_H

// TODO: proper read and write functions from the serial, not needed now so lazy

#define SERIAL_COM1_BASE 0x3f8
#define SERIAL_COM2_BASE 0x2f8

#define SERIAL_DATA_PORT(base)              (base)
#define SERIAL_INTERRUPT_COMMAND_PORT(base) (base + 1)
#define SERIAL_FIFO_COMMAND_PORT(base)      (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)      (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base)     (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)       (base + 5)

#define SERIAL_LINE_ENABLE_DLAB 0x80

void serial_configure_baud_rate(short com, short divisor);
void serial_configure_interrupt(short com);
void serial_configure_line(short com);
void serial_configure_buffer(short com);
void serial_configure_modem(short com);

int serial_is_transmit_fifo_empty(int com);

char read_serial(short com);
void write_serial(short com, char a);

void serial_init();

#endif // GAMEOS_SERIAL_H