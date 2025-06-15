#include "idt/idt.h"
#include "stdio.h"
#include <stdbool.h>
#include <stdint.h>

int main()
{
	load_idt();
	kprintf("Welcome to the kernel!\n");
	int x = 1 / 0;
}
