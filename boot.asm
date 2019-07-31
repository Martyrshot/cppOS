bits 16
org 0x7c00 ; I'm guessing this is for the magic location qemu looks for code. Need to read more

boot:
	mov ax, 0x2401
	int 0x15 ; enables A20 gate. The A20 gate enables a larger memory space. Not present on modern intel chips
		 ; This is a stupid workaround for legacy support of the old 8086 where some programmers would overflow
		 ; a memory address to 0 rather than just indexing lower memory...
	
	mov ax, 0x3 ; vga text mode 3
	int 0x10

	mov [disk], dl ; store the disk location in memory for later
	
	mov ah, 0x2 ; request to read sectors
	mov al, 1 ; sectors to read
	mov ch, 0 ; cylinder idx
	mov dh, 0 ; head idx
	mov cl, 2 ; sector idx
	mov dl, [disk] ; disk idx
	mov bx, copy_target ; target
	int 0x13 ; perform request
	cli ; clear interrupts
	lgdt [gdt_pointer] ; load global descriptor table
	mov eax, cr0 ; The next three instructions enable protected mode
	or eax, 0x1
	mov cr0, eax
	mov ax, DATA_SEG ; point all remaining segments to the data segments
	mov ds, ax ; data segment
	mov es, ax ; extra segment
	mov fs, ax ; general purpose segment
	mov gs, ax ; general purpose segment
	mov ss, ax ; stack segment
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
	db 10010010b ; Access layout -- present, ring level, 1, executable, direction, read/write/accessed
	db 11001111b ; flags layout -- granularity, size, 0, 0, limit_high
	db 0x0 ; Base 24:41
gdt_end:
gdt_pointer:
	dw gdt_end - gdt_start ; size
	dd gdt_start ; pointer address
disk:
	db 0x0
CODE_SEG equ gdt_code - gdt_start ; offset inside GDT of code segment
DATA_SEG equ gdt_data - gdt_start ; offset inside GDT of data segment

times 510 - ($-$$) db 0 ; Zero out everything else
dw 0xaa55 ; magic number to indicate bootable
copy_target:
bits 32
	hello: db "Hello more than 512 bytes world!!",0 ; Message with tombstone character
boot2:
	mov esi, hello ; address of greeting message
	mov ebx, 0xb8000 ; memory location of output buffer
.loop:
	lodsb ; loads a byte into AX from (E)SI and increments (E)SI by one
	or al, al ; Have we printed everything?
	jz halt ; If yes, halt
	or eax, 0x0F00 ; mask to apply colour to text
	mov word [ebx], ax ; push masked character to output buffer
	add ebx, 2 ; increment index buffer
	jmp .loop
halt:
	cli ; clear interrupts
	hlt ; halt
times 1024 - ($-$$) db 0  
