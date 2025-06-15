#ifndef IO_H
#define IO_H

#include <stdint.h>

void kernel_panic();
static inline void outb(uint16_t port, uint8_t val)
{
	__asm__ volatile("outb %b0, %w1" : : "a"(val), "Nd"(port) : "memory");
}

static inline uint8_t inb(uint16_t port)
{
	uint8_t ret;
	__asm__ volatile("inb %w1, %b0" : "=a"(ret) : "Nd"(port) : "memory");
	return ret;
}

static inline void io_wait(void)
{
	outb(0x80, 0);
}

uint8_t __attribute__((cdecl)) EnableInterrupts();
uint8_t __attribute__((cdecl)) DisableInterrupts();

#endif // !IO_H
