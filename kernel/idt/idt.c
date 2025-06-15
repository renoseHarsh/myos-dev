#include "idt.h"
#include "isr.h"
#include <stdint.h>

IDTEntry idtGates[256];

IDTDescriptor idt;

void set_idt_gate(int interrupt, uint32_t handler, uint16_t segment,
                  uint8_t flags)
{
	idtGates[interrupt].lowoffset = handler & 0xFFFF;
	idtGates[interrupt].highoffset = (handler >> 16) & 0xFFFF;
	idtGates[interrupt].segment = segment;
	idtGates[interrupt].zero = 0;
	idtGates[interrupt].flag = flags;
}

void load_idt()
{

	ISR_Initialize();
	idt.offset = idtGates;
	idt.size = sizeof(idtGates) - 1;
	__asm__ __volatile__("lidt %0" : : "m"(idt));
}
