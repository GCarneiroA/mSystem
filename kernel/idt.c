#include <system.h>

// Tabelas de descritores de interrupção

typedef struct
{
    uint16          base_lo;
    uint16          sel;
    uint8           always0;
    uint8           flags;
    uint16          base_hi;
} __attribute__((packed)) idt_entry;

#define IDT_DESCRIPTOR_INTERRUPT_GATE   0x8e

#define IDT_DESCRIPTOR_TRAP_GATE        0x8f

typedef struct
{
    uint16          limit;
    uint32          base;
} __attribute__((packed)) idt_ptr;

idt_entry idt[256];
idt_ptr idtp;

void set_idt_gate(uint8 num, uint32 base, uint16 sel, uint8 flags)
{
    idt[num].base_lo = (base & 0xFFFF);
    idt[num].base_hi = (base >> 16) & 0xFFFF;

    idt[num].sel = sel;
    idt[num].always0 = 0;
    idt[num].flags = flags;
}

void set_idt_interrupt_gate(uint8 num, uint32 base)
{
    set_idt_gate(num, base, 0x08, IDT_DESCRIPTOR_INTERRUPT_GATE);
}

void set_idt_trap_gate(uint8 num, uint32 base)
{
    set_idt_gate(num, base, 0x08, IDT_DESCRIPTOR_TRAP_GATE);
}

extern void idt_load();

void install_idt()
{
    idtp.limit = (sizeof(idt_entry) * 256) - 1;
    idtp.base = (uint32) &idt;

    memset((uint8*) &idt, 0, sizeof(idt_entry) * 256);

    idt_load();
}