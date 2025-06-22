gcc := i686-elf-gcc
asm := nasm

cflags := -O0 -ffreestanding -m32 -g -c -Wall
# ldflags := -T linker.ld -ffreestanding -O0 -nostdlib -lgcc -m32
ldflags := -ffreestanding -O0 -nostdlib -lgcc -m32 -Wl,-Ttext,0x100000

c_src := $(shell find kernel -name '*.c')
asm_src := $(shell find kernel -name '*.asm')

c_obj := $(patsubst kernel/%.c, build/%.o, $(c_src))
asm_obj := $(patsubst kernel/%.asm, build/%.o, $(asm_src))

obj := $(c_obj) $(asm_obj)

dirs := $(sort $(dir $(c_obj)))

all: build/bootable.bin

prepare:
	@mkdir -p $(dirs)

build/bootable.bin: build/bootloader.bin build/loader.bin build/kernel.bin
	cat $^ > $@

build/bootloader.bin: bootloader/bootloader.asm
	$(asm) $< -f bin -o $@

build/kernel.bin: build/kernel.elf
	i686-elf-objcopy -O binary $< $@
	truncate -s 256512 $@

build/kernel.elf: $(c_obj) $(asm_obj) 
	$(gcc) $(ldflags) -o $@ $^


build/loader.bin: bootloader/loader.asm
	$(asm) $< -f bin -o $@

build/%.o: kernel/%.c | prepare
	$(gcc) $(cflags) $< -o $@

build/%.o: kernel/%.asm | prepare
	$(asm) $< -f elf -o $@


clean:
	rm -rf build/*
