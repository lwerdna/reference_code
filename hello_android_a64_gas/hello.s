// NOTES:
// kernel call: syscall number in x8, args in x0, x1, x2, ...
// syscall number lookup <kernel-source-dir>/include/uapi/asm-generic/unistd.h 
// 
.global	_start, _test

.text

_start:
	bl		_test

	ldr		x1, =msg0

	mov		x2, msg0_len		// arg2: message length

	// TODO: explore in detail why this won't work
	//mov		x1, msg			// arg1: message

	// we can also access the string by getting the 4k page and adding the offset
	//adrp	x1, msg0
	//add		x1, x1, :lo12:msg0

	mov		x0, #1			// arg0: stdout
	
	mov		x8, #64			// __NR_write
	svc		#0
	
	mov		x0, #0			// arg0: status
	mov		x8, #94			// __NR_exit
	svc		#0

_test:
	// test Binja instrinsic _CountLeadingZeros()
	clz		x1, x0
	ldr		x0, =0xDEADBEEF
	ret

.data

msg0:
	.asciz "Hello, world!\n"
msg0_len = . - msg0

msg1:
	.asciz "I'm in test()\n"
msg1_len = . - msg1

