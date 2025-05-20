all: build/bootable.bin

build/bootloader.bin: bootloader/bootloader.asm
	nasm $< -f bin -o $@

build/kernel.o: kernel/kernel.c
	i686-elf-gcc -ffreestanding -m32 -g -c $< -o $@

build/loader.o: bootloader/loader.asm
	nasm $< -f elf -o $@

build/kernel.bin: build/loader.o build/kernel.o
	i686-elf-ld -o $@ -Ttext 0x1000 $^ --oformat binary

build/bootable.bin: build/bootloader.bin build/kernel.bin
	cat $^ > $@
