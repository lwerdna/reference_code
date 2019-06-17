all: hello_intel hello_att

hello_att.o: hello_att.S
	as --32 ./hello_att.S -o hello_att.o

hello_att: hello_att.o
	ld -m elf_i386 hello_att.o -o hello_att

hello_intel.o: hello_intel.S
	as --32 ./hello_intel.S -o hello_intel.o

hello_intel: hello_intel.o
	ld -m elf_i386 hello_intel.o -o hello_intel
