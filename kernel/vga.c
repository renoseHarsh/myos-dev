#include "vga.h"
#include <stdbool.h>
#include <stdint.h>

#define VGA_MEMORY (uint16_t *)0xB8000
#define columns 80
#define rows 25

static uint16_t vga_color = 7; // Grey on Black
static uint16_t *const vga_buffer = VGA_MEMORY;
static int cursor_row = 0;
static int cursor_col = 0;

static void outb(uint16_t port, uint8_t data)
{
    __asm__("outb %0, %1" ::"a"(data), "d"(port));
}

static void vga_scroll()
{
    for (int crow = 1; crow < rows; crow++) {
        for (int ccol = 0; ccol < columns; ccol++) {
            vga_buffer[((crow - 1) * columns) + ccol]
                = vga_buffer[(crow * columns) + ccol];
        }
    }
    for (int ccol = 0; ccol < columns; ccol++) {
        vga_buffer[((rows - 1) * columns) + ccol] = 0;
    }
}

static void vga_move_cursor()
{
    uint16_t pos = cursor_row * columns + cursor_col;
    outb(0x3D4, 0x0E);
    outb(0x3D5, pos >> 8);
    outb(0x3D4, 0x0F);
    outb(0x3D5, pos);
}

void vga_set_color(const enum vga_color bg, const enum vga_color fg)
{
    vga_color = (bg << 4 | fg);
}

void vga_clear()
{
    vga_set_color(VGA_COLOR_BLACK, VGA_COLOR_GRAY);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            vga_buffer[(i * columns) + j] = vga_color << 8;
        }
    }
    cursor_col = 0;
    cursor_row = 0;
    vga_move_cursor();
}

void vga_putc(const char c)
{
    if (cursor_row == rows) {
        vga_scroll();
        cursor_row = rows - 1;
    }
    if (c == '\n') {
        cursor_row++;
        cursor_col = 0;
    } else {
        vga_buffer[(cursor_row * columns) + cursor_col++]
            = (vga_color << 8) | c;
        if (cursor_col == columns) {
            cursor_row++;
            cursor_col = 0;
        }
    }
    vga_move_cursor();
}

void vga_puts(const char *str)
{
    for (; *str != '\0'; str++)
        vga_putc(*str);
}
