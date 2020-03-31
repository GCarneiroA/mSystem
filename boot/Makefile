

AS := as
LD := ld
IFS := imagefs
RM := del

all: boot.bin ndst.bin clean

boot.bin: boot.out
	objcopy -O binary -j .text boot.out boot.bin
	copy boot.bin ..

boot.out: boot.o
	$(LD) -o boot.out boot.o -Ttext 0x7c00

boot.o: boot.s bootsector.s functions.s macros.s
	$(AS) -o boot.o boot.s

ndst.bin: ndst.out
	objcopy -O binary -j .text ndst.out ndst.bin
	copy ndst.bin ..

ndst.out: ndst.o
	$(LD) -o ndst.out ndst.o -Ttext 0x0

ndst.o: ndst.s bootsector.s functions.s macros.s
	$(AS) -o ndst.o ndst.s

clean:
	$(RM) *.o
	$(RM) *.out
	$(RM) *.bin
