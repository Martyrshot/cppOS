.PHONY: all clean

all: run

run: kernel.bin
	qemu-system-x86_64 -fda kernel.bin

boot.o: boot.asm
	nasm -f elf32 boot.asm -o boot.o

kernel.bin: boot.o proc.cpp kernmain.cpp lib/trimminglinkedlist.a
	i386-elf-g++ proc.cpp kernmain.cpp boot.o -o kernel.bin -nostdlib -ffreestanding -std=c++11 \
	-mno-red-zone -fno-exceptions -nostdlib -fno-rtti -Wall -Wextra -Werror -T link.ld \-Iinclude/

lib/trimminglinkedlist.a: lib/trimminglinkedlist.o
	ar rvs lib/trimminglinkedlist.a lib/trimminglinkedlist.o

lib/trimminglinkedlist.o: lib/trimminglinkedlist.cpp
	i386-elf-g++ lib/trimminglinkedlist.cpp -c -o lib/trimminglinkedlist.o -nostdlib -ffreestanding -std=c++11 \
	-mno-red-zone -fno-exceptions -nostdlib -fno-rtti -Wall -Wextra -Werror -Iinclude/
clean:
	rm -rf lib/*.o
	rm -rf lib/*.a
	rm -rf kernel.bin
	rm -rf *.o
