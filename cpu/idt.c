#include "idt.h"
#include "../libc/stdint.h"

#define INTERRUPT 0
#define TRAP 1

#define PL0 0x0
#define PL3 0x3

#define TRAP_0_GATE(idx)                                           \
    create_idt_descriptor(idx, (uint32_t)&isr##idx, \
                          TRAP, PL0);

#define DECLARE_INTERRUPT_HANDLER(i) void isr##i(void)

/* Protected mode exceptions interrupts */
DECLARE_INTERRUPT_HANDLER(0);
DECLARE_INTERRUPT_HANDLER(1);
DECLARE_INTERRUPT_HANDLER(2);
DECLARE_INTERRUPT_HANDLER(3);
DECLARE_INTERRUPT_HANDLER(4);
DECLARE_INTERRUPT_HANDLER(5);
DECLARE_INTERRUPT_HANDLER(6);
DECLARE_INTERRUPT_HANDLER(7);
DECLARE_INTERRUPT_HANDLER(8);
DECLARE_INTERRUPT_HANDLER(9);
DECLARE_INTERRUPT_HANDLER(10);
DECLARE_INTERRUPT_HANDLER(11);
DECLARE_INTERRUPT_HANDLER(12);
DECLARE_INTERRUPT_HANDLER(13);
DECLARE_INTERRUPT_HANDLER(14);
DECLARE_INTERRUPT_HANDLER(15);
DECLARE_INTERRUPT_HANDLER(16);
DECLARE_INTERRUPT_HANDLER(17);
DECLARE_INTERRUPT_HANDLER(18);
DECLARE_INTERRUPT_HANDLER(19);

/* IRQs */
DECLARE_INTERRUPT_HANDLER(32);
DECLARE_INTERRUPT_HANDLER(33);
DECLARE_INTERRUPT_HANDLER(34);
DECLARE_INTERRUPT_HANDLER(35);
DECLARE_INTERRUPT_HANDLER(36);
DECLARE_INTERRUPT_HANDLER(37);
DECLARE_INTERRUPT_HANDLER(38);
DECLARE_INTERRUPT_HANDLER(39);
DECLARE_INTERRUPT_HANDLER(40);
DECLARE_INTERRUPT_HANDLER(41);
DECLARE_INTERRUPT_HANDLER(42);
DECLARE_INTERRUPT_HANDLER(43);
DECLARE_INTERRUPT_HANDLER(44);
DECLARE_INTERRUPT_HANDLER(45);
DECLARE_INTERRUPT_HANDLER(46);
DECLARE_INTERRUPT_HANDLER(47);

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct idt_ptr idt_ptr_t;

struct idt_descriptor
{
    uint16_t handler_low;
    uint16_t code_segsel;
    uint8_t zero;
    uint8_t config;
    uint16_t handler_high;
} __attribute__((packed));
typedef struct idt_descriptor idt_descriptor_t;

idt_descriptor_t idt[256];

void load_idt(uint32_t);

void handle_syscall(void);

void create_idt_descriptor(uint32_t n, uint32_t handler, uint8_t type, uint8_t pl)
{
    idt_descriptor_t descriptor;
    descriptor.handler_low = handler & 0x0000FFFF;
    descriptor.handler_high = (handler >> 16) & 0x0000FFFF;
    descriptor.code_segsel = 0x08;
    descriptor.zero = 0;
    descriptor.config = (0x1 << 7) | ((pl & 0x03) << 5) | (0x01 << 3) | (0x01 << 2) | (0x01 << 1) | type;
    idt[n] = descriptor;
}

void idt_init()
{
    idt_ptr_t idt_base;
    idt_base.base = (uint32_t)&idt;
    idt_base.limit = 256 * sizeof(idt_descriptor_t) - 1;

    /* Protected mode exceptions */
    TRAP_0_GATE(0);
    TRAP_0_GATE(1);
    TRAP_0_GATE(2);
    TRAP_0_GATE(3);
    TRAP_0_GATE(4);
    TRAP_0_GATE(5);
    TRAP_0_GATE(6);
    TRAP_0_GATE(7);
    TRAP_0_GATE(8);
    TRAP_0_GATE(9);
    TRAP_0_GATE(10);
    TRAP_0_GATE(11);
    TRAP_0_GATE(12);
    TRAP_0_GATE(13);
    TRAP_0_GATE(14);
    TRAP_0_GATE(15);
    TRAP_0_GATE(16);
    TRAP_0_GATE(17);
    TRAP_0_GATE(18);
    TRAP_0_GATE(19);

    /* IRQs */
    TRAP_0_GATE(32);
    TRAP_0_GATE(33);
    TRAP_0_GATE(34);
    TRAP_0_GATE(35);
    TRAP_0_GATE(36);
    TRAP_0_GATE(37);
    TRAP_0_GATE(38);
    TRAP_0_GATE(39);
    TRAP_0_GATE(40);
    TRAP_0_GATE(41);
    TRAP_0_GATE(42);
    TRAP_0_GATE(43);
    TRAP_0_GATE(44);
    TRAP_0_GATE(45);
    TRAP_0_GATE(46);
    TRAP_0_GATE(47);

    // PL3 Syscall trap
    // create_idt_descriptor(0xAE, (uint32_t)&handle_syscall, TRAP, PL3);

    load_idt((uint32_t)&idt_base);
}