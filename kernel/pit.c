#include <system.h>
#include <irq.h>
#include <isr.h>

int timer_ticks = 0;

void timer_phase(int hz)
{
    int divisor = 1193180 / hz;
    outportb(0x43, 0x36);
    outportb(0x40, divisor & 0xFF);
    outportb(0x40, divisor >> 8);
}

void timer_handler(regs *r)
{
    timer_ticks++;
}

void timer_install()
{
    irq_install_handler(0, timer_handler);
}

void timer_wait(uint32 ticks)
{
    unsigned long eticks = timer_ticks + ticks;
    while (timer_ticks < eticks);
}