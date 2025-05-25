gcc := i686-elf-gcc
asm := nasm

cflags := -O0 -ffreestanding -m32 -g -c -Wall
# ldflags := -T linker.ld -ffreestanding -O0 -nostdlib -lgcc -m32
ldflags := -ffreestanding -O0 -nostdlib -lgcc -m32 -Wl,-Ttext,0x1000

src := $(wildcard kernel/*.c)
obj := $(src:kernel/%.c=build/%.o)

build/bootable.bin: build/bootloader.bin build/kernel.bin
	cat $^ > $@

build/bootloader.bin: bootloader/bootloader.asm
	$(asm) $< -f bin -o $@

build/kernel.bin: build/kernel.elf
	i686-elf-objcopy -O binary $< $@

build/kernel.elf: build/loader.o $(obj)
	$(gcc) $(ldflags) -o $@ $^

build/loader.o: bootloader/loader.asm
	$(asm) $< -f elf -o $@

build/%.o: kernel/%.c
	$(gcc) $(cflags) $< -o $@

clean:
	rm -rf build/*
