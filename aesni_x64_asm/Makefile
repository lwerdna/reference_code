.PHONY: all

all: encrypt decrypt

encrypt.o: encrypt.asm
	nasm -f macho64 encrypt.asm -o encrypt.o

encrypt: encrypt.o
	ld -macosx_version_min 10.7.0 -lSystem encrypt.o -o encrypt

decrypt.o: decrypt.asm
	nasm -f macho64 decrypt.asm -o decrypt.o

decrypt: decrypt.o
	ld -macosx_version_min 10.7.0 -lSystem decrypt.o -o decrypt
