global WinMain
extern ExitProcess, GetStdHandle, WriteConsoleA
;extern _ExitProcess@4, _GetStdHandle@4, _WriteConsoleA@20

section .text
WinMain:

    mov		ecx, -11				; STD_OUTPUT_HANDLE
    call    GetStdHandle

    push    0
    mov		r9, numCharsWritten
    mov		r8, msg.len
    mov		rdx, msg
    mov		rcx, rax
    call    WriteConsoleA
    add		rsp, 0x8

    mov		rcx, 0
    call    ExitProcess

section .data
msg:
	db		"Hello, world!", 0x0a
	.len:   equ	$ - msg

section .bss
numCharsWritten               resd 1
