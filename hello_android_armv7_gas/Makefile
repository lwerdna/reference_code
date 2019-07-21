all: hello

NDK = $(HOME)/android-ndk-r15c
AS = $(NDK)/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-as
LD = $(NDK)/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-ld

hello: hello.o
	# see `ld -V` for other -m options
	$(LD) -m elf32-littlearm hello.o -o hello

hello.o: hello.s
	 $(AS) hello.s -o hello.o

clean:
	rm -f hello hello.o a.out
