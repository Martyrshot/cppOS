.PHONY: all clean

all: run

run: kerncpp
	qemu-system-x86_64 -fda kernel.bin

bootasm: boot.asm
	nasm -f elf32 boot.asm -o boot.o

kerncpp: bootasm kernmain.cpp
	i386-elf-g++ kernmain.cpp boot.o -o kernel.bin -nostdlib -ffreestanding -std=c++11 -mno-red-zone \
	-fno-exceptions -nostdlib -fno-rtti -Wall -Wextra -Werror -T link.ld \-Iinclude/


clean:
	rm -rf kernel.bin
	rm -rf *.o
