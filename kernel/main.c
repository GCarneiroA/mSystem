#include <system.h>
#include <irq.h>
#include <pit.h>

void start_kernel()
{
	__asm__ __volatile__("xchg %bx, %bx");
	
	install_gdt();
	install_idt();
	install_isrs();

	__asm__ __volatile__("cli");
	install_irq();
	__asm__ __volatile__("sti");

	keyboard_install();
	
	timer_install();
	
	init_video();
	
	__asm__ __volatile__("xchg %bx, %bx");
	
mylabel:
	goto mylabel;
}
