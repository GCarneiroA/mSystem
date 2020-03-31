#include <system.h>
#include <idt.h>
#include <irq.h>

int timer_ticks = 0;

void timer_phase(int hz)
{
    int divisor = 1193180 / hz;
    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
}

void timer_handler(INT_REGS *r)
{
    timer_ticks++;
}

void timer_install()
{
    irq_install_handler(0, timer_handler);
}