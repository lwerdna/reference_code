# https://developer.arm.com/downloads/-/arm-gnu-toolchain-downloads

all: hello

TOOLCHAIN = $(HOME)/arm-gnu-toolchain-13.2.Rel1-darwin-arm64-aarch64-none-elf

SYSROOT = $(TOOLCHAIN)/aarch64-none-elf

GCC = $(TOOLCHAIN)/bin/aarch64-none-elf-gcc

hello: hello.c
	$(GCC) -dumpmachine
	#$(GCC) hello.c -o hello --sysroot=$(SYSROOT) --specs=nosys.specs -lc
	$(GCC) hello.c -o hello --specs=nosys.specs

clean:
	rm -f hello
