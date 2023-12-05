all: hello

TOOLCHAIN = $(HOME)/arm-gnu-toolchain-13.2.rel1

SYSROOT = $(TOOLCHAIN)/aarch64-none-elf

GCC = $(TOOLCHAIN)/bin/aarch64-none-elf-gcc

hello: hello.c
	#$(GCC) hello.c -o hello --sysroot=$(SYSROOT) --specs=nosys.specs -lc
	$(GCC) hello.c -o hello --specs=nosys.specs

clean:
	rm -f hello
