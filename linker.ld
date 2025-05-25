ENTRY(_start)

SECTIONS
{
    . = 0x1000;

    /* Code section */
    .text : {
        *(.text)
    }
    /* Initialized data section */
    .data : {
        *(.data)
    }

    /* Uninitialized data section (bss) */
    .bss : {
        *(COMMON)
        *(.bss)
    }
}
