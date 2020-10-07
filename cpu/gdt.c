#include "gdt.h"
#include "../libc/stdint.h"

// TODO: update gdt entry creation for more control

#define SEG_BASE 0x0000
#define SEG_LIMIT 0xFFFF
#define PL0 0x0
#define PL3 0x3
#define CODE 0xA
#define DATA 0x2

struct gdt_ptr {
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));
typedef struct gdt_ptr gdt_ptr_t;

struct gdt_entry {
    uint16_t limit;
    uint16_t base_low;
    uint8_t base_mid;
    uint8_t access;
    uint8_t granularity;
    uint8_t base_high;
} __attribute__((packed));
typedef struct gdt_entry gdt_entry_t;

gdt_entry_t gdt_entries[5];

// void gdt_create_entry(uint32_t n, uint16_t base, uint16_t limit, uint8_t pl, uint8_t type) {
//     gdt_entry_t entry;
//     entry.limit = (SEG_LIMIT & 0xFFFF);
//     entry.base_low = (SEG_BASE & 0xFFFF);
//     entry.base_mid = (SEG_BASE & 0xFF);
//     entry.access = (0x01 << 7) | ((pl & 0x03) << 5) | (0x01 << 4) | (type & 0x0F);
//     entry.granularity |= (0x01 << 7) | (0x01 << 6) | 0x0F;
//     entry.base_high = (SEG_BASE & 0xFF);
//     gdt_entries[n] = entry;
// }

void gdt_create_entry(uint32_t n, uint8_t access, uint8_t granularity) {
    gdt_entries[n].limit = (SEG_LIMIT & 0xFFFF);
    gdt_entries[n].base_low = (SEG_BASE & 0xFFFF);
    gdt_entries[n].base_mid = ((SEG_BASE >> 16) & 0xFF);
    gdt_entries[n].base_high = ((SEG_BASE >> 24) & 0xFF);
    gdt_entries[n].access = access;
    gdt_entries[n].granularity = granularity;
}

void load_gdt(uint32_t);

void gdt_init()
{
    gdt_ptr_t gdt_base;
    gdt_base.limit = sizeof(uint64_t) * 5;
    gdt_base.base = (uint32_t)&gdt_entries;

    gdt_create_entry(0, 0, 0);
    gdt_create_entry(1, 0x9A, 0xCF);
    gdt_create_entry(2, 0x92, 0xCF);
    gdt_create_entry(3, 0xFA, 0xCF);
    gdt_create_entry(4, 0xF2, 0xCF);

    // gdt_create_entry(0, 0, 0, 0, 0);
    // gdt_create_entry(1, SEG_BASE, SEG_LIMIT, PL0, CODE);
    // gdt_create_entry(2, SEG_BASE, SEG_LIMIT, PL0, DATA);
    // gdt_create_entry(3, SEG_BASE, SEG_LIMIT, PL3, CODE);
    // gdt_create_entry(4, SEG_BASE, SEG_LIMIT, PL3, DATA);

    // gdt_entries[0] = 0x0000000000000000;
    // gdt_entries[1] = 0x00CF9A000000FFFF;
    // gdt_entries[2] = 0x00CF92000000FFFF;
    // gdt_entries[3] = 0x00CFFA000000FFFF;
    // gdt_entries[4] = 0x00CFF2000000FFFF;

    load_gdt((uint32_t)&gdt_base);
}