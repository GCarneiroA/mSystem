#include <system.h>

typedef struct
{
    uint16 limit_low;
    uint16 base_low;
    uint8 base_middle;
    uint8 access;
    uint8 granularity;
    uint8 base_high;
} __attribute__((packed)) gdt_entry;

typedef struct
{
    uint16 limit;
    uint32 base;
} __attribute__((packed)) gdt_ptr;

gdt_entry gdt[3];
gdt_ptr gdtp;

extern void gdt_flush();

void gdt_set_gate(int32 num, unsigned long base, unsigned long limit, uint8 access, uint8 gran)
{
    gdt[num].base_low = (base & 0xFFFF);
    gdt[num].base_middle = (base >> 16) & 0xFF;
    gdt[num].base_high = (base >> 24) & 0xFF;

    gdt[num].limit_low = (limit & 0xFFFF);
    gdt[num].granularity = ((limit >> 16) & 0x0F);

    gdt[num].granularity |= (gran & 0xF0);
    gdt[num].access = access;
}

void install_gdt()
{
    gdtp.limit = (sizeof(gdt_entry) * 3) - 1;
    gdtp.base = (uint32) &gdt;

    gdt_set_gate(0, 0, 0, 0, 0);
    gdt_set_gate(1, 0, 0xFFFFFFFF, 0x9A, 0xCF);
    gdt_set_gate(2, 0, 0xFFFFFFFF, 0x92, 0xCF);
    
    gdt_flush();
}