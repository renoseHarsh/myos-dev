org 0x9000
section .text
	global _start
	extern main
	bits 32

_start:
; Print Loading message
	push load_msg
	push 0xB8000
	call print_string
	add esp, 8


	; Select Driver
	mov al, 0xE0
	mov dx, 0x1F6
	out dx, al

	; Sector count to 0x1F2
	mov al, 50
	mov dx, 0x1F2
	out dx, al

	; Low 8 bits to 0x1F3
	mov al, 0x02
	mov dx, 0x1F3
	out dx, al

	; Mid 8 bits to 0x1F4
	mov al, 0
	mov dx, 0x1F4
	out dx, al

	; High 8 bits to 0x1F5
	mov dx, 0x1F5
	out dx, al

	; Send command 0x20 to 0x1F7
	mov al, 0x20
	mov dx, 0x1F7
	out dx, al

	mov edi, 0x100000 ; Destination address for data
	mov ebx, 50 ; Number of sectors to read
	read_all_data:
		; Wait for BSY to clear
		mov dx, 0x1F7
		.poll_clear:
			in al, dx
			test al, 0x01
			jnz ata_error
			test al, 0x08
			jz .poll_clear

		; Read data from 0x1F0
		mov dx, 0x1F0
		mov ecx, 256
		.read_data:
			in ax, dx
			mov [edi], ax
			add edi, 2
			loop .read_data

		dec ebx
		jnz read_all_data
	
	push done_msg
	push 0xB8000 + (2 * 80)
	call print_string
	add esp, 8

	jmp 0x08:0x100000

	hang:
		cli
		hlt
		jmp hang

	ata_error:
		mov dx, 0x1F1
		in al, dx
		push error_msg
		push 0xB8000 + (2 * 80)
		call print_string
		add esp, 8
		jmp hang

	print_string:
		mov ebx, [esp + 8]
		mov edx, [esp + 4]
		xor ax, ax
		mov ecx, 0
		.loop_print:
			mov ah, 7
			mov al, [ebx + ecx]
			mov [edx + ecx * 2], ax
			inc ecx
			cmp al, 0
			jne .loop_print
		ret

load_msg:
	db "Loading Kernel", 0
done_msg:
	db "Kernel Loaded", 0
error_msg:
	db "Error Loading Kernel", 0
times 512 - ($ - $$) db 0
