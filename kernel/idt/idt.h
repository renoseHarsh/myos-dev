#ifndef IDT_H
#define IDT_H

#include <stdint.h>

typedef struct {
	uint16_t lowoffset;
	uint16_t segment;
	uint8_t zero;
	uint8_t flag;
	uint16_t highoffset;

} __attribute__((packed)) IDTEntry;

typedef struct {
	uint16_t size;
	IDTEntry *offset;
} __attribute__((packed)) IDTDescriptor;

void load_idt();
void set_idt_gate(int interrupt, uint32_t handler, uint16_t segment,
                  uint8_t flags);

#endif
