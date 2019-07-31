bits 16
org 0x7c00

boot:
	mov si, welcome
	mov ah, 0x0e ; write char in TTY mode
  .loop:
	lodsb
	or al, al
	jz halt
	int 0x10
	jmp .loop

  halt:
	cli
	hlt
  welcome: db "This is a test bootloader", 0

  times 510 - ($-$$) db 0
  dw 0xaa55 ; magic number
