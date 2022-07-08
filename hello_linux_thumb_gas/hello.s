.data

/* Data segment: define our message string and calculate its length. */
msg:
    .ascii      "Hello, world!\n"
len = . - msg

.text

/* Our application's entry point. */
.globl _start

/* without this directive, thumb code will still be generated with -mthumb
   passed to as, but the pointer to this entrypoint elf32_hdr.e_entry will
   not have LSB set */
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
