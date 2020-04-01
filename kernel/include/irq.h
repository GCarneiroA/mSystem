#ifndef __IRQ_H
#define __IRQ_H

#include <isr.h>

extern void install_irq();
extern void irq_install_handler(int irq, void(*handler)(regs *r));
extern void irq_uninstall_handler(int irq);

#endif