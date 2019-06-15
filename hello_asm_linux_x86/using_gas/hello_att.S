.global _start

.text

_start:
	movl $len, %edx
	movl $msg, %ecx
	movl $1, %ebx
	movl $4, %eax					# sys_write
	int $0x80

	movl $0, %ebx
	movl $1, %eax					# sys_exit
	int	$0x80

.data
msg:
	.ascii    "Hello, World!\n"
	len = . - msg
