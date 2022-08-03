.text

.globl _start, _test

.thumb_func
_start:
    bl      _test
    mov     %r0, $0
    mov     %r7, $1
    swi     $0

.thumb_func
_test:
    push    {r1, r2, r3, lr}
    ldr     %r0, =0xDEADBEEF
    msr     basepri, r3
    pop     {r1, r2, r3, pc}

