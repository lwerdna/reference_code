global WinMain
;extern ExitProcess, GetStdHandle, WriteConsoleA
extern _ExitProcess@4, _GetStdHandle@4, _WriteConsoleA@20

section .text
WinMain:

    push    -11				; STD_OUTPUT_HANDLE
    call    _GetStdHandle@4

    push    0
    push    numCharsWritten
    push    msg.len
    push    msg
    push    eax
    call    _WriteConsoleA@20

    push    0
    call    _ExitProcess@4

section .data
msg:
	db		"Hello, world!", 0x0a
	.len:   equ	$ - msg

section .bss
numCharsWritten               resd 1
