ENTRY(start)

SECTIONS {
    /* sets load address to MiB (convention) */
    . = 1M;

    .boot :
    {
        /* ensure that the multiboot header is at the beginning */
        KEEP(*(.multiboot_header))
    }

    .text :
    {
        *(.text)
    }
} 
