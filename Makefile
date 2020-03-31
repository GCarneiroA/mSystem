

RM := del
IFS := imagefs


all: mSystem.img boot.bin ndst.bin clean

mSystem.img: boot.bin ndst.bin kernel.bin
	$(IFS) c mSystem.img 720
	$(IFS) b mSystem.img boot.bin
	$(IFS) a mSystem.img ndst.bin
	$(IFS) a mSystem.img kernel.bin

boot.bin:
	$(MAKE) -C boot/ boot.bin

ndst.bin:
	$(MAKE) -C boot/ ndst.bin

kernel.bin:
	$(MAKE) -C kernel/ kernel.bin

clean:
	$(RM) *.bin
	$(MAKE) -C boot/ clean
	$(MAKE) -C kernel/ clean