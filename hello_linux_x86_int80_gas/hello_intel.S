.intel_syntax noprefix

.global _start

.text

_start:
	mov edx, offset len
	mov	ecx, offset msg
	mov ebx, 1
	mov eax, 4					# sys_write
	int 0x80

	mov	ebx, 0
	mov eax, 1					# sys_exit
	int	0x80

.data
msg:
	.ascii    "Hello, World!\n"
	len = . - msg
