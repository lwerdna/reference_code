all: hello

TOOLS = $(NDK)/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi

hello: hello.o
	# see `ld -V` for other -m options
	$(TOOLS)-ld hello.o -o hello

hello.o: hello.s
	 $(TOOLS)-as hello.s -o hello.o

disasm:
	$(TOOLS)-objdump --disassemble hello

clean:
	rm -f hello hello.o a.out
