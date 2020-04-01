AS := as
RM := del
CC := gcc
CFLAGS := -Wall -fno-builtin -nostdlib -ffreestanding -nostdinc -m32 -I./include

all: kernel.bin

kernel.bin: kernel.out
	objcopy -O binary kernel.out kernel.bin
	copy kernel.bin ..

kernel.out: kernel.o isr_asm.o gdt_asm.o idt_asm.o irq_asm.o main.o system.o mem.o port.o gdt.o idt.o irq.o isr.o pit.o display.o string.o kb.o
	$(CC) $(CFLAGS) -T link.ld -o kernel.out kernel.o isr_asm.o gdt_asm.o idt_asm.o irq_asm.o main.o system.o mem.o gdt.o idt.o irq.o isr.o port.o pit.o display.o string.o kb.o -e start

kb.o: kb.c
	$(CC) $(CFLAGS) -o kb.o -c kb.c

gdt.o: gdt.c
	$(CC) $(CFLAGS) -o gdt.o -c gdt.c

idt.o: idt.c
	$(CC) $(CFLAGS) -o idt.o -c idt.c

irq.o: irq.c
	$(CC) $(CFLAGS) -o irq.o -c irq.c

isr.o: isr.c
	$(CC) $(CFLAGS) -o isr.o -c isr.c

pit.o: pit.c
	$(CC) $(CFLAGS) -o pit.o -c pit.c

mem.o: mem.c
	$(CC) $(CFLAGS) -o mem.o -c mem.c

port.o: port.c
	$(CC) $(CFLAGS) -o port.o -c port.c

system.o: system.c
	$(CC) $(CFLAGS) -o system.o -c system.c

string.o: string.c
	$(CC) $(CFLAGS) -o string.o -c string.c

display.o: display.c
	$(CC) $(CFLAGS) -o display.o -c display.c

main.o:
	$(CC) $(CFLAGS) -o main.o -c main.c

gdt_asm.o: gdt_asm.s
	$(AS) -o gdt_asm.o gdt_asm.s

idt_asm.o: idt_asm.s
	$(AS) -o idt_asm.o idt_asm.s

irq_asm.o: irq_asm.s
	$(AS) -o irq_asm.o irq_asm.s

isr_asm.o: isr_asm.s
	$(AS) -o isr_asm.o isr_asm.s

kernel.o: kernel.s
	$(AS) -o kernel.o kernel.s

clean:
	$(RM) *.o
	$(RM) *.out
	$(RM) *.bin