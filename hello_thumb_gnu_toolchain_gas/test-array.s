.thumb
.syntax unified

.global _start



.text

.thumb_func
_start:
	push    {r3, r4, r5, r6, r7, lr}
	ldr		r5, =p_thing
	
	ldr     r6, =index
	ldr     r7, [r6]
	bl      die
	ldr     r3, [r5]
	ldr     r2, =array
	mov     r0, r0
	subs    r0, r0, r3
	str		r0, [r2, r7, lsl #2]
	pop     {r3, r4, r5, r6, r7, pc}

die:
	ldr		r0, =0xDEAD
	bx		lr

.ltorg

.data
p_thing:
	.word	thing
index:
	.word	0
thing:
	.word	0
array:
	.word	0
	.word	0

