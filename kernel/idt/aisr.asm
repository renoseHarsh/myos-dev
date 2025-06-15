bits 32
extern isr_handler


%macro ISR_NOERRORCODE 1

global ISR%1:
ISR%1:
	push 0
	push %1
	jmp isr_common

%endmacro

%macro IST_ERRORCODE 1

global ISR%1:
ISR%1:
	push %1
	jmp isr_common

%endmacro

%include "kernel/idt/isr_defines.inc"


isr_common:
	pushad

	push esp
	call isr_handler
	add esp, 4

	popad
	iret
