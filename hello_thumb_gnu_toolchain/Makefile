# https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

all: hello

TOOLCHAIN = $(HOME)/arm-gnu-toolchain-13.2.Rel1-darwin-arm64-arm-none-eabi

SYSROOT = $(TOOLCHAIN)/arm-none-elf

GCC = $(TOOLCHAIN)/bin/arm-none-eabi-gcc

hello: hello.c
	#$(GCC) hello.c -o hello --sysroot=$(SYSROOT) --specs=nosys.specs -lc
	$(GCC) -mthumb hello.c -gdwarf -o hello --specs=nosys.specs

clean:
	rm -f hello
