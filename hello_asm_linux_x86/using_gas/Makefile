all: hello_intel

hello_intel.o: hello_intel.S
	as --32 ./hello_intel.S -o hello_intel.o

hello_intel: hello_intel.o
	ld -m elf_i386 hello_intel.o -o hello_intel
