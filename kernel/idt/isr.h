#ifndef ISR_H
#define ISR_H

#include <stdint.h>

typedef struct {
	uint32_t di, si, bp, sp, bx, dx, cx, ax;
	uint32_t interrupt;
	uint32_t error_code, eip, cs, eflags;
} __attribute__((packed)) Registers;

void initialize_isr_gates();
typedef void (*isr_t)(Registers *regs);
void ISR_Initialize();
void register_interrupt_handler(int n, isr_t handler);

#endif
