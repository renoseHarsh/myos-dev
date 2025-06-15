#include "isr.h"
#include "../stdio.h"
#include "io.h"
#include "pic.h"
#include <stdbool.h>

static isr_t interrupt_handlers[256];

static const char *const g_Exceptions[] = { "Divide by zero error",
	                                        "Debug",
	                                        "Non-maskable Interrupt",
	                                        "Breakpoint",
	                                        "Overflow",
	                                        "Bound Range Exceeded",
	                                        "Invalid Opcode",
	                                        "Device Not Available",
	                                        "Double Fault",
	                                        "Coprocessor Segment Overrun",
	                                        "Invalid TSS",
	                                        "Segment Not Present",
	                                        "Stack-Segment Fault",
	                                        "General Protection Fault",
	                                        "Page Fault",
	                                        "",
	                                        "x87 Floating-Point Exception",
	                                        "Alignment Check",
	                                        "Machine Check",
	                                        "SIMD Floating-Point Exception",
	                                        "Virtualization Exception",
	                                        "Control Protection Exception ",
	                                        "",
	                                        "",
	                                        "",
	                                        "",
	                                        "",
	                                        "",
	                                        "Hypervisor Injection Exception",
	                                        "VMM Communication Exception",
	                                        "Security Exception",
	                                        "" };

void __attribute__((cdecl)) isr_handler(Registers *regs)
{
	if (interrupt_handlers[regs->interrupt]) {
		interrupt_handlers[regs->interrupt](regs);
	} else if (regs->interrupt >= 32) {
		kprintf("Unhandled interrupt: %d\n", regs->interrupt);
		PIC_sendEOI(regs->interrupt - 32);
	} else {
		kprintf("Unhandled exception %d %s\n", regs->interrupt,
		        g_Exceptions[regs->interrupt]);
		kprintf("eax=%x ebx=%x ecx=%x edx=%x esi=%x edi=%x\n", regs->ax,
		        regs->bx, regs->cx, regs->dx, regs->si, regs->di);
		kprintf("eip=%x cs=%x eflags=%x\n", regs->eip, regs->cs, regs->eflags);
		kprintf("interrupt=%d error_code=%x\n", regs->interrupt,
		        regs->error_code);
		kernel_panic();
	}
}

void register_interrupt_handler(int n, isr_t handler)
{
	interrupt_handlers[n] = handler;
}

void ISR_Initialize()
{
	initialize_isr_gates();
}
