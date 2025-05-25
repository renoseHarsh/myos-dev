#include "vga.h"
#include <stdbool.h>
int main()
{
    for (int i = 0; i < 26; i++) {
        vga_putc('A' + i % 26);
    }
}
