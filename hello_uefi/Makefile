#PATH_CLANG = $(HOME)/Downloads/clang+llvm-15.0.0-x86_64-apple-darwin
PATH_CLANG = $(HOME)/Downloads/clang+llvm-17.0.1-arm64-apple-darwin22.0

CLANG = $(PATH_CLANG)/bin/clang
LD_LLD = $(PATH_CLANG)/bin/ld.lld
LLD_LINK = $(PATH_CLANG)/bin/lld-link
LD64 = $(PATH_CLANG)/bin/ld64.lld
LLC = $(PATH_CLANG)/bin/llc

CFLAGS := -O0 -ffreestanding -MMD -mno-red-zone -std=c11 -target x86_64-unknown-windows
LDFLAGS := -flavor link -subsystem:efi_application -entry:efi_main

SRCS := main.c

default: all
all: bootx64.efi
.PHONY: clean all default

%.o: %.c
	$(CLANG) $(CFLAGS) -c $< -o $@

bootx64.efi: main.o
	$(LD_LLD) $(LDFLAGS) $< -out:$@
	./postprocess.py ./bootx64.efi

-include $(SRCS:.c=.d)

clean:
	rm -f main.o main.d bootx64.efi
