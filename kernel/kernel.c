#include "idt/idt.h"
#include "idt/irq.h"
#include "stdio.h"
#include <stdbool.h>
#include <stdint.h>

int main()
{
	load_idt();
	IRQ_Initialize();
	kprintf("Welcome to the kernel!\n");
	for (;;) {
	}
}
