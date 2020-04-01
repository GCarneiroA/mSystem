#include <system.h>
#include <irq.h>
#include <idt.h>

#define PIC_EOI                 0x20


#define PIC_MASTER_CMD_PORT     0x20
#define PIC_MASTER_DATA_PORT    0x21


#define PIC_SLAVE_CMD_PORT      0xA0
#define PIC_SLAVE_DATA_PORT     0xA1


extern void irq0();
extern void irq1();
extern void irq2();
extern void irq3();
extern void irq4();
extern void irq5();
extern void irq6();
extern void irq7();
extern void irq8();
extern void irq9();
extern void irq10();
extern void irq11();
extern void irq12();
extern void irq13();
extern void irq14();
extern void irq15();

void *irq_routines[16] = 
{
    0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0, 0, 0
};

void irq_install_handler(int irq, void(*handler)(regs *r))
{
    irq_routines[irq] = handler;
}

void irq_uninstall_handler(int irq)
{
    irq_routines[irq] = 0;
}

void remap_PIC()
{
    outportb(PIC_MASTER_CMD_PORT,  0x11);  /* Tell master PIC to wait for 3 initialization bytes. */
    io_wait();
    outportb(PIC_SLAVE_CMD_PORT,   0x11);  /* Tell slave PIC to wait for 3 initialization bytes. */
    io_wait();
    outportb(PIC_MASTER_DATA_PORT, 0x20);  /* Remap: set master PIC offset to 0x20 (32). */
    io_wait();
    outportb(PIC_SLAVE_DATA_PORT,  0x28);  /* Remap: set slave PIC offset to 0x28 (40).  */
    io_wait();
    outportb(PIC_MASTER_DATA_PORT, 0x04);  /* Tell master PIC that there is a slave PIC at IRQ2 (bit mask 0000 0100) */
    io_wait();
    outportb(PIC_SLAVE_DATA_PORT,  0x02);  /* Tell slave PIC that its cascade identity is 2 (0000 0010) */
    io_wait();
    outportb(PIC_MASTER_DATA_PORT, 0x01);  /* Set master PIC operation mode to 8086/8088 (MCS-80/85) mode. */
    io_wait();
    outportb(PIC_SLAVE_DATA_PORT,  0x01);  /* Set slave PIC operation mode to 8086/8088 (MCS-80/85) mode. */
    io_wait();
    outportb(PIC_MASTER_DATA_PORT, 0x00);  /* Clear master PIC mask. */
    outportb(PIC_SLAVE_DATA_PORT,  0x00);  /* Clear slave PIC mask. */
}

void install_irq()
{
    remap_PIC();

    set_idt_interrupt_gate(32, (unsigned)irq0);
	set_idt_interrupt_gate(33, (unsigned)irq1);
	set_idt_interrupt_gate(34, (unsigned)irq2);
	set_idt_interrupt_gate(35, (unsigned)irq3);
	set_idt_interrupt_gate(36, (unsigned)irq4);
	set_idt_interrupt_gate(37, (unsigned)irq5);
	set_idt_interrupt_gate(38, (unsigned)irq6);
	set_idt_interrupt_gate(39, (unsigned)irq7);
	set_idt_interrupt_gate(40, (unsigned)irq8);
	set_idt_interrupt_gate(41, (unsigned)irq9);
	set_idt_interrupt_gate(42, (unsigned)irq10);
	set_idt_interrupt_gate(43, (unsigned)irq11);
	set_idt_interrupt_gate(44, (unsigned)irq12);
	set_idt_interrupt_gate(45, (unsigned)irq13);
	set_idt_interrupt_gate(46, (unsigned)irq14);
	set_idt_interrupt_gate(47, (unsigned)irq15);
}

void irq_handler(regs *r)
{
    void (*handler)(regs *r);

    handler = irq_routines[r->int_no - 32];
    if (handler)
    {
        handler(r);
    }

    if (r->int_no >= 40)
    {
        outportb(PIC_SLAVE_CMD_PORT, PIC_EOI);
    }

    outportb(PIC_MASTER_CMD_PORT, PIC_EOI);
}