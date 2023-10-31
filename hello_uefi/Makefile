CLANG = $(HOME)/Downloads/clang+llvm-15.0.0-x86_64-apple-darwin/bin/clang
LD_LLD = $(HOME)/Downloads/clang+llvm-15.0.0-x86_64-apple-darwin/bin/ld.lld
LLD_LINK = $(HOME)/Downloads/clang+llvm-15.0.0-x86_64-apple-darwin/bin/lld-link
LD64 = $(HOME)/Downloads/clang+llvm-15.0.0-x86_64-apple-darwin/bin/ld64.lld
LLC = $(HOME)/Downloads/clang+llvm-15.0.0-x86_64-apple-darwin/bin/llc

CFLAGS := -ffreestanding -MMD -mno-red-zone -std=c11 -target x86_64-unknown-windows
LDFLAGS := -flavor link -subsystem:efi_application -entry:efi_main

SRCS := main.c

default: all
all: bootx64.efi
.PHONY: clean all default

%.o: %.c
	$(CLANG) $(CFLAGS) -c $< -o $@

bootx64.efi: main.o
	$(LD_LLD) $(LDFLAGS) $< -out:$@

-include $(SRCS:.c=.d)

clean:
	rm -f main.o main.d bootx64.efi
