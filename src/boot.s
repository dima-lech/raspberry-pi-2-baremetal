.section ".text.boot"

.globl _start
_start:
    # Setup the stack.
    mov sp, #0x8000

    bl entry_c

halt:
    wfe
    b halt

.globl do_nothing
do_nothing:
    bx lr
