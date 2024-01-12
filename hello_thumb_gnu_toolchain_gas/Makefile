# https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

all: hello

TOOLCHAIN = $(HOME)/arm-gnu-toolchain-13.2.Rel1-darwin-arm64-arm-none-eabi

SYSROOT = $(TOOLCHAIN)/arm-none-elf

AS = $(TOOLCHAIN)/bin/arm-none-eabi-as
LD = $(TOOLCHAIN)/bin/arm-none-eabi-ld
GCC = $(TOOLCHAIN)/bin/arm-none-eabi-gcc
OBJDUMP = $(TOOLCHAIN)/bin/arm-none-eabi-objdump

hello: hello.o
	$(LD) hello.o -o hello

hello.o: hello.s
	 $(AS) -mthumb hello.s -o hello.o

disasm:
	$(OBJDUMP) -d hello.o

clean:
	rm -f hello hello.o a.out
