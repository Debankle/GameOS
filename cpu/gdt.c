#include "gdt.h"
#include "../libc/stdint.h"

#define SEG_BASE 0
#define SEG_LIMIT 0x000FFFFF

// Yes I know these can be replaced with static hex numbers but this 
// way it is obvious what bits are what because this GDT has been 
// giving me massive headaches so i made it as dynamic as possible
#define GRAN(x) ((x) << 0x3)
#define SIZE(x) ((x) << 0x2)
#define SYS_AVAILABLE(x) ((x) << 0x1)
#define PRESENT(x) ((x) << 0x7)
#define PRIVILAGE(x) ((x & 0x03) << 0x5)
#define DESCRIPTOR(x) ((x) << 0x4)
#define EXEC(x) ((x) << 0x3)
#define DIRECTION(x) ((x) << 0x2)
#define READWRITE(x) ((x) << 0x1)
#define ACCESSED(X) ((X) << 0x0)

#define FLAG GRAN(1) | SIZE(1) | (0 << 0x1) | (0 << 0x0)
#define CODE_0 PRESENT(1) | PRIVILAGE(0) | DESCRIPTOR(1) | EXEC(1) | DIRECTION(0) | READWRITE(1) | ACCESSED(0)
#define DATA_0 PRESENT(1) | PRIVILAGE(0) | DESCRIPTOR(1) | EXEC(0) | DIRECTION(0) | READWRITE(1) | ACCESSED(0)
#define CODE_3 PRESENT(1) | PRIVILAGE(3) | DESCRIPTOR(1) | EXEC(1) | DIRECTION(0) | READWRITE(1) | ACCESSED(0)
#define DATA_3 PRESENT(1) | PRIVILAGE(3) | DESCRIPTOR(1) | EXEC(0) | DIRECTION(0) | READWRITE(1) | ACCESSED(0)

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

struct gdt_descriptor {
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t flags;
    uint8_t base_high;
} __attribute__((packed));
typedef struct gdt_descriptor gdt_descriptor_t;

gdt_descriptor_t gdt[5];

void load_gdt(uint32_t);

void create_descriptor(uint32_t n, uint32_t base, uint32_t limit, uint16_t access, uint8_t flag)
{
    gdt_descriptor_t descriptor;

    descriptor.limit = limit;
    descriptor.base_low = base;
    descriptor.base_mid = base & 0x000FF;
    descriptor.access = access;
    descriptor.flags = ((flag << 4) & 0xF0) | (limit & 0xF);
    descriptor.base_high = base & 0xFF;

    gdt[n] = descriptor;
}


void gdt_init()
{
    gdt_ptr_t gdt_base;
    gdt_base.limit = sizeof(uint64_t) * 5;
    gdt_base.base = (uint32_t)&gdt;

    create_descriptor(0, 0, 0, 0, 0);
    create_descriptor(1, SEG_BASE, SEG_LIMIT, CODE_0, FLAG);
    create_descriptor(2, SEG_BASE, SEG_LIMIT, DATA_0, FLAG);
    create_descriptor(3, SEG_BASE, SEG_LIMIT, CODE_3, FLAG);
    create_descriptor(4, SEG_BASE, SEG_LIMIT, DATA_3, FLAG);

    load_gdt((uint32_t)&gdt_base);
}