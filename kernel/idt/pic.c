#include "pic.h"
#include "io.h"

#define PIC1 0x20
#define PIC2 0xA0
#define PIC1_COMMAND PIC1
#define PIC1_DATA (PIC1 + 1)
#define PIC2_COMMAND PIC2
#define PIC2_DATA (PIC2 + 1)

#define PIC_EOI	0x20

#define ICW1_ICW4 0x01
#define ICW1_INIT 0x10

void PIC_Initialize(uint8_t offset1, uint8_t offset2)
{
	// IWC1: Initialize the PIC
	outb(PIC1_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();
	outb(PIC2_COMMAND, ICW1_INIT | ICW1_ICW4);
	io_wait();

	// ICW2: Set the vector offsets
	outb(PIC1_DATA, offset1);
	io_wait();
	outb(PIC2_DATA, offset2);
	io_wait();

	// ICW3: Tell the master PIC that there is a slave PIC at IRQ2
	outb(PIC1_DATA, 4);
	io_wait();
	outb(PIC2_DATA, 2);
	io_wait();

	// ICW4: Set the mode of operation
	outb(PIC1_DATA, 0x01);
	io_wait();
	outb(PIC2_DATA, 0x01);
	io_wait();

	// Unmask both PICs.
	outb(PIC1_DATA, 0);
	outb(PIC2_DATA, 0);
}

void PIC_disable(void)
{
	outb(PIC1_DATA, 0xff);
	outb(PIC2_DATA, 0xff);
}


void PIC_sendEOI(uint8_t irq)
{
	if(irq >= 8)
		outb(PIC2_COMMAND,PIC_EOI);
	
	outb(PIC1_COMMAND,PIC_EOI);
}


#define PIC_READ_IRR 0x0A
#define PIC_READ_ISR 0x0B

static inline uint16_t __pic_get_irq_reg(int ocw3)
{
    outb(PIC1_COMMAND, ocw3);
    outb(PIC2_COMMAND, ocw3);
    return (inb(PIC2_COMMAND) << 8) | inb(PIC1_COMMAND);
}

uint16_t PIC_get_irr(void)
{
    return __pic_get_irq_reg(PIC_READ_IRR);
}

uint16_t PIC_get_isr(void)
{
    return __pic_get_irq_reg(PIC_READ_ISR);
}

