org 0x7c00
bits 16

; Enter Text mode
mov ah, 0
mov al, 03h
int 10h

; Load Kernel Into memory
mov ah, 02h
mov al, 10
mov ch, 0
mov cl, 2
mov dh, 0
mov bx, 0x1000
int 0x13

cli
lgdt [GDT_Descriptor]
mov eax, cr0
or al, 1
mov cr0, eax

jmp code_sel:protected_mode

halt:
	cli
	hlt

bits 32
protected_mode:
	mov ax, data_sel
	mov ds, ax
	mov ss, ax
	mov es, ax
	mov fs, ax
	mov gs, ax

	mov ebp, 0x90000
	mov esp, ebp

	jmp code_sel:0x1000

	hlt

gdt_start:
	dq 0
	
	code_desc:
		dw 0xFFFF				; limit lower 16 bits
		dw 0x0000				; Base lower 16 bits
		db 0x00 				; Base middle 8 bits
		db 10011010b		; Access byte 8 bits
		db 11001111b		; limit high 4 bits & flag 4 bits
		db 0x00					; Base high 8 bits

	data_desc:
		dw 0xFFFF				; limit lower 16 bits
		dw 0x0000				; Base lower 16 bits
		db 0x00 				; Base middle 8 bits
		db 10010010b		; Access byte 8 bits
		db 11001111b		; limit high 4 bits & flag 4 bits
		db 0x00					; Base high 8 bits

gdt_end:

GDT_Descriptor:
	dw gdt_end - gdt_start - 1
	dd gdt_start

; Code selected at 0x08
code_sel equ code_desc - gdt_start
; Data selector at 0x16
data_sel equ data_desc - gdt_start

times 510 - ($-$$) db 0
db    0x55, 0xaa
