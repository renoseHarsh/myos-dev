#include "vga.h"
#include <stdbool.h>
int main()
{
    int nex = 0;
    while (true) {
        for (int i = 0; i < 26; i++) {
            vga_putc('A' + ((nex + i) % 26));
        }
        nex++;
        vga_putc('\n');
        if (nex % 2) vga_set_color(VGA_COLOR_GRAY, VGA_COLOR_BLACK);
        else vga_set_color(VGA_COLOR_BLACK, VGA_COLOR_GRAY);
    }
}
