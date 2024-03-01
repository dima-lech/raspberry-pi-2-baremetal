ENTRY(_start)

SECTIONS
{
    . = 0x8000;

    .text :
    {
        KEEP(*(.text.boot))
        *(.text*)
    }

    .rodata :
    {
        *(.rodata*)
        . = ALIGN(4K);
    }

    /DISCARD/ :
    {
        *(.comment)
    }
}
