all: hello

TOOLS=$(NDK)/toolchains/aarch64-linux-android-4.9/prebuilt/darwin-x86_64/bin/aarch64-linux-android

hello: hello.o
	# see `ld -V` for other -m options
	$(TOOLS)-ld -m aarch64elf hello.o -o hello

hello.o: hello.s
	$(TOOLS)-as hello.s -o hello.o

disasm: hello
	$(TOOLS)-objdump --disassemble ./hello

clean:
	rm -f hello hello.o
