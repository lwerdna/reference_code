all: hello

NDK = $(HOME)/android-ndk-r15c
AS = $(NDK)/toolchains/aarch64-linux-android-4.9/prebuilt/darwin-x86_64/bin/aarch64-linux-android-as
LD = $(NDK)/toolchains/aarch64-linux-android-4.9/prebuilt/darwin-x86_64/bin/aarch64-linux-android-ld

hello: hello.o
	# see `ld -V` for other -m options
	$(LD) -m aarch64elf hello.o -o hello

hello.o: hello.s
	 $(AS) hello.s -o hello.o

clean:
	rm -f hello hello.o
