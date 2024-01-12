.thumb
.syntax unified

.data

/* Data segment: define our message string and calculate its length. */
msg:
    .ascii      "Hello, THUMB!\n"
len = . - msg

.text

.globl _start, test_literal_pool, test_4498

/* from https://peterdn.com/post/2019/02/03/hello-world-in-arm-assembly/ */
/* Our application's entry point. */
.thumb_func
_start:
	/* syscall write(int fd, const void *buf, size_t count) */
	mov		%r0, $1		/* fd := STDOUT_FILENO */
	ldr		%r1, =msg	/* buf := msg */
	ldr		%r2, =len	/* count := len */
	mov		%r7, $4		/* write is syscall #4 */
	swi		$0			/* invoke syscall */

	/* syscall exit(int status) */
	mov		%r0, $0		/* status := 0 */
	mov		%r7, $1		/* exit is syscall #1 */
	swi		$0			/* invoke syscall */

test_literal_pool:
	ldr		%r0, =0x1AAAAAAA
	ldr		%r1, =0x1BBBBBBB
	ldr		%r2, =0x1CCCCCCC
	ldr		%r3, =0x1DDDDDDD
	ldr		%r4, =0x1EEEEEEE
	ldr		%r5, =0x1FFFFFF1
	bx		%lr

literal_pool:
.ltorg

/* https://github.com/Vector35/binaryninja-api/issues/4498 */
.thumb_func
test_4498:
	push	{r7, lr}
	mls		%r3, %r0, %r1, %r2
	subs	%r4, 3
	ite		cc
	rsbcc	%r3, %r3, $4
	rsbcs	%r3, %r3, $6
	mov		%r0, %r3
	pop		{r7, pc}

.end


