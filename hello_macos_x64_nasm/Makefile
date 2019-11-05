.PHONY: all

all: hello

hello.o: hello.asm
	nasm -f macho64 hello.asm -o hello.o

hello: hello.o
	ld -macosx_version_min 10.7.0 -lSystem hello.o -o hello

