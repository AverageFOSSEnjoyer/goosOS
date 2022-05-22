/* bootloader entry point */
ENTRY(boot)     

SECTIONS {
    /* start section at 1MB to be recognized by the bootloader */
    . = 1M;     

    /* reference multiboot header and text for bootloader */
    .text BLOCK(4K) : ALIGN(4K) {
        *(.multiboot)
        *(.text)
    }

    /* read only data section */
    .rodata BLOCK(4K) : ALIGN(4K) {
        *(.rodata)
    }

    /* initialized general data section */
    .data BLOCK(4K) : ALIGN(4k) {
        *(.data)
    }

    /* uninitialized data section and stack */
    .bss BLOCK(4K) : ALIGN(4K) {
        *(COMMON)
        *(.bss)
    }
}