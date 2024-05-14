ENTRY(_start)

SECTIONS
{
    . = ENTRY_ADDRESS;

    .text :
    {
        KEEP(*(.text.boot))
        *(.text*)
        . = ALIGN(4K);
    }

    .rodata :
    {
        *(.rodata*)
        . = ALIGN(4K);
    }

	.data :
    {
        *(.data*)
        *(.sdata*)
        *(.data.rel)
        . = ALIGN(4K);
    }

    .bss :
    {
        __bss_start = .;

        *(.bss)
        *(.sbss)

        __bss_end = .;

        . = ALIGN(4K);
    }

    /DISCARD/ :
    {
        *(.comment)
    }
}
