global	_start

	section .text
_start:
	;   user-apps: rdi, rsi, rdx, rcx, r8 and r9
	; kernel call: rdi, rsi, rdx, r10, r8 and r9 (syscall number in rax)
	mov		rdx, msglen		; arg2: message length
	mov		rsi, msg		; arg1: message
	mov		rdi, 1			; arg0: stdout
	; /usr/include/x86_64-linux-gnu/asm/unistd_64.h
	mov		rax, 1			; __NR_write
	syscall
	
	mov		rdi, 0			; arg0: status
	mov		rax, 60			; __NR_exit
	syscall

	section .data
msg:		db	"Hello, world!", 0x0a, 0
msglen:	equ	$ - msg
