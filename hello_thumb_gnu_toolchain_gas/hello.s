/* from https://peterdn.com/post/2019/02/03/hello-world-in-arm-assembly/ */

.data

/* Data segment: define our message string and calculate its length. */
msg:
    .ascii      "Hello, ARM!\n"
len = . - msg

.text

.globl _start, test

/* Our application's entry point. */
.thumb_func
_start:
    /* syscall write(int fd, const void *buf, size_t count) */
    mov     %r0, $1     /* fd := STDOUT_FILENO */
    ldr     %r1, =msg   /* buf := msg */
    ldr     %r2, =len   /* count := len */
    mov     %r7, $4     /* write is syscall #4 */
    swi     $0          /* invoke syscall */

    /* syscall exit(int status) */
    mov     %r0, $0     /* status := 0 */
    mov     %r7, $1     /* exit is syscall #1 */
    swi     $0          /* invoke syscall */

.thumb_func
test:
	ldr		%r0, =0x1AAAAAAA
	ldr		%r1, =0x1BBBBBBB
	ldr		%r2, =0x1CCCCCCC
	ldr		%r3, =0x1DDDDDDD
	ldr		%r4, =0x1EEEEEEE
	ldr		%r5, =0x1FFFFFF1
	bx		%lr

