#ifndef GAMEOS_INTERRUPT_H
#define GAMEOS_INTERRUPT_H

#include "../libc/stdint.h"

struct registers {
    uint32_t ds;
    uint32_t edi, esi, ebp, esp, ebx, edx, ecx, eax; // Pushed by pusha.
    uint32_t int_no, err_code;                       // Interrupt number and error code (if applicable)
    uint32_t eip, cs, eflags, useresp, ss;           // Pushed by the processor automatically.
};
typedef struct registers registers_t;

void enable_interrupts(void);
void disable_interrupts(void);
void interrupt_handler(registers_t regs);

#endif // GAMEOS_INTERRUPT_H