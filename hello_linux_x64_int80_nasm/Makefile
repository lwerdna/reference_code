all: hello

hello: hello.o
	# see `ld -V` for other -m options
	ld -m elf_x86_64 hello.o -o hello

hello.o: hello.s
	nasm hello.s -f elf64 -o hello.o

clean:
	rm -f hello hello.o
