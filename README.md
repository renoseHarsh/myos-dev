# myos-dev

This is a hobby operating system written in C and Assembly, developed from scratch. It boots in a bare-metal environment using a custom bootloader and runs on emulators like QEMU. The kernel provides basic low-level functionality and serves as a foundation for learning OS development and hardware interaction.

---

## ✅ Completed Features

- [x] Custom bootloader (`bootloader.asm`, `loader.asm`)
- [x] Kernel written in C (`kernel.c`)
- [x] Basic VGA text mode driver (`vga.c`, `vga.h`)
- [x] Screen clearing and colored text output (`vga_set_color`, `vga_clear`, `vga_putc`, `vga_puts`)
- [x] VGA scrolling and cursor movement (internal to `vga.c`)
- [x] Build system using `Makefile`
- [x] Compiles to bootable binary (`bootable.bin`, `kernel.bin`, etc.)

---

## 🔧 Planned Features

- [ ] Minimal freestanding libc implementation
  - [ ] `memcpy`, `memset`, `strlen`, `strcmp`, `strcpy`
  - [ ] `printf`, `putchar`, `puts`, `scanf`
- [ ] Concurrecny
- [ ] Virtualization
  - [ ] Paging 
- [ ] Networking

---

## 🛠 Build Instructions

Make sure you have a cross-compiler (e.g., `i686-elf-gcc`) installed and then run:

```bash
make
```

To run in QEMU:

```bash
qemu-system-i386 -kernel build/bootable.bin
```
