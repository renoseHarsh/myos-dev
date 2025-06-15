#include "util.h"
#include "stdio.h"

void kernel_panic()
{
	__asm__ __volatile__("cli");
	kprintf("\n*** KERNEL PANIC ***\n");
	kprintf("System halted.\n");
	for (;;) {
		__asm__ __volatile__("hlt");
	}
}
