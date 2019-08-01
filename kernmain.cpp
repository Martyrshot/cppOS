#include <proc.h>

extern "C" void kmain()
{
	const short color[15] = {0x0100,0x0200,0x0300,0x0400,0x0500,0x0600,0x0700,0x0800,0x0900,0x0A00,0x0B00,0x0C00,0x0D00,0x0E00,0x0F00};
	const char *hello = "Hello cpp world!";
	short *vga = (short *)0xb8000;
	Proc p(0, true);
	for (int i = 0; i < 16; i++) {
		vga[i+80] = color[i] | hello[i];
	}
}
