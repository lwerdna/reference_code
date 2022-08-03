all: test

TOOLS=$(NDK)/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi

test.o: test.s
	$(TOOLS)-as -mcpu=cortex-m0 ./test.s -o test.o

test: test.o
	$(TOOLS)-ld test.o -o test

disasm:
	$(TOOLS)-objdump --disassemble test

entry:
	$(TOOLS)-readelf --file-header test | grep 'Entry point'

clean:
	rm -f test.o test
