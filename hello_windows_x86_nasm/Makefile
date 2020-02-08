all: hello.exe

hello.exe: hello.obj
	link hello.obj /ENTRY:WinMain /SUBSYSTEM:CONSOLE /OUT:hello.exe kernel32.lib
	
hello.obj: hello.asm
	nasm -f win32 hello.asm -o hello.obj

clean:
	del /Q hello.exe hello.obj
