all: hello

hello: hello.o
	ld -m elf_i386 hello.o -o hello

hello.o: hello.s
	nasm hello.s -f elf32 -o hello.o
