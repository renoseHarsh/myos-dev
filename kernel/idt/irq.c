#include "irq.h"
#include "../stdio.h"
#include "io.h"
#include "isr.h"
#include "pic.h"
#include <stddef.h>

#define PIC_REMAP_OFFSET 0x20

IRQHandler irq_handlers[16];

void IRQ_Handler(Registers *regs)
{
	int irq = regs->interrupt - PIC_REMAP_OFFSET;

	uint8_t pic_isr = PIC_get_isr();
	uint8_t pic_irr = PIC_get_irr();

	if (irq_handlers[irq] != NULL) {
		irq_handlers[irq](regs);
	} else {
		kprintf("Unhandled IRQ %d  ISR=%x  IRR=%x\n", irq, pic_isr, pic_irr);
	}

	PIC_sendEOI(irq);
}

void timer(Registers *regs)
{
	kprintf(".");
}

void IRQ_Initialize()
{
	PIC_Initialize(PIC_REMAP_OFFSET, PIC_REMAP_OFFSET + 8);

	// Clear all IRQ handlers
	for (int i = 0; i < 16; i++)
		register_interrupt_handler(PIC_REMAP_OFFSET + i, IRQ_Handler);

	irq_handlers[0] = timer;

	EnableInterrupts();
}

void IRQ_RegisterHandler(int irq, IRQHandler handler)
{
	if (irq < 0 || irq >= 16) {
		kprintf("Invalid IRQ number: %d\n", irq);
		return;
	}

	irq_handlers[irq] = handler;
}
