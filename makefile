.PHONY: all

all: boot.asm
	nasm -f bin boot.asm -o boot.bin && qemu-system-x86_64 -fda boot.bin


clean:
	rm boot.bin
