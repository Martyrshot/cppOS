bits 16
org 0x7c00 ; I'm guessing this is for the magic location qemu looks for code. Need to read more

boot:
	mov ax, 0x2401
	int 0x15 ; enables A20 gate. The A20 gate enables a larger memory space. Not present on modern intel chips
		 ; This is a stupid workaround for legacy support of the old 8086 where some programmers would overflow
		 ; a memory address to 0 rather than just indexing lower memory...
	mov ax, 0x3 ; vga text mode 3
	int 0x10

	lgdt [gdt_pointer] ; load global descriptor table
	mov eax, cr0 ; The next three instructions enable protected mode
	or eax, 0x1
	mov cr0, eax
	jmp CODE_SEG:boot2 ; Load the CODE_SEG into CS, and boot2 into IP


gdt_start:
	dq 0x0
gdt_code:
	dw 0xFFFF ; base describes where segment begins -- limit_low, base_low
	dw 0x0 ; base_middle, access, flags, base_high
	db 0x0 ; Base 16:23
	db 10011010b ; Access layout -- present, ring level, 1, executable, direction, read/write/accessed
	db 11001111b ; flags layout -- granularity, size, 0, 0, limit_high
	db 0x0 ; Base 24:41
gdt_data:
	dw 0xFFFF ; base describes where segment begins -- limit_low, base_low
	dw 0x0 ; base_middle, access, flags, base_high
	db 0x0 ; Base 16:23
	db 10011010b ; Access layout -- present, ring level, 1, executable, direction, read/write/accessed
	db 11001111b ; flags layout -- granularity, size, 0, 0, limit_high
	db 0x0 ; Base 24:41
gdt_end:


gdt_pointer:
	dw gdt_end - gdt_start ; size
	dd gdt_start ; pointer address

CODE_SEG equ gdt_code - gdt_start ; offset inside GDT of code segment
DATA_SEG equ gdt_data - gdt_start ; offset inside GDT of data segment

bits 32
boot2:
	mov ax, DATA_SEG ; point all remaining segments to the data segments
	mov ds, ax ; data segment
	mov es, ax ; extra segment
	mov fs, ax ; general purpose segment
	mov gs, ax ; general purpose segment
	mov ss, ax ; stack segment

	mov esi, hello
	mov ebx, 0xb8000
  .loop:
	lodsb ; loads a byte into AX from (E)SI and increments (E)SI by one
	or al, al ; Have we printed everything?
	jz halt ; If yes, halt
	or eax, 0x0F00 ; mask to apply colour to text
	mov word [ebx], ax ; push masked character to output buffer
	add ebx, 2 ; increment index buffer
	jmp .loop
  halt:
	cli
	hlt
  hello: db "Hello world!",0
  times 510 - ($-$$) db 0
  dw 0xaa55
