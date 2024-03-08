.section ".text.boot"

.globl _start
_start:

    /* Setup the stack */
    mov sp, #0x10000

    /* Load BSS addresses */
    ldr r4, =__bss_start
    ldr r9, =__bss_end

    /* Zeroize BSS */
    mov r5, #0
    mov r6, #0
    mov r7, #0
    mov r8, #0
    b       2f
1:
    stmia r4!, {r5-r8}
2:
    cmp r4, r9
    blo 1b

    /* Jump to C entry function */
    bl entryC


    /* Should not reach here! */
halt:
    wfe
    b halt

