#include "vga.h"
#include <stdarg.h>

static int print_digit(int n)
{
	if (n == 0) return 0;
	int count = print_digit(n / 10);
	vga_putc(n % 10 + '0');
	return count + 1;
}

static int print_hex(unsigned int n)
{
	if (n == 0) return 0;
	int count = print_hex(n / 16);
	int hex = n % 16;
	vga_putc(hex > 9 ? hex % 10 + 'a' : hex + '0');
	return count + 1;
}

static int print_int(int n, const int base)
{
	int count = 0;
	if (base == 10 && n < 0) {
		vga_putc('-');
		n = -n;
		count++;
	}
	if (n == 0) {
		vga_putc('0');
		return 1;
	}
	switch (base) {
		case 10: {
			count += print_digit(n);
			break;
		}
		case 16: {
			count += print_hex((unsigned int)n);
			break;
		}
	}
	return count;
}

static int print_str(const char *str)
{
	int count = 0;
	while (*str != '\0') {
		vga_putc(*str++);
		count++;
	}
	return count;
}

int kprintf(const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	int count = 0;

	while (*fmt != '\0') {
		if (*fmt == '%') {
			switch (*(++fmt)) {
				case 'd': {
					count += print_int(va_arg(args, int), 10);
					break;
				}
				case 'x': {
					count += print_int(va_arg(args, int), 16);
					break;
				}
				case 'c': {
					count++;
					vga_putc((char)va_arg(args, int));
					break;
				}
				case 's': {
					count += print_str(va_arg(args, char *));
					break;
				}
			}
		} else {
			vga_putc(*fmt);
			count++;
		}
		fmt++;
	}

	va_end(args);
	return count;
}
