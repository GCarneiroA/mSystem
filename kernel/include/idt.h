#ifndef __IDT_H
#define __IDT_H

extern void set_idt_interrupt_gate(uint8 num, uint32 base);
extern void set_idt_trap_gate(uint8 num, uint32 base);
extern void load_idt();
extern void install_idt();

#endif