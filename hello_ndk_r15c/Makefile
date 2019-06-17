NDK = $(HOME)/android-ndk-r15c

SYSR = $(NDK)/platforms/android-23/arch-arm
GCC = $(NDK)/toolchains/arm-linux-androideabi-4.9/prebuilt/darwin-x86_64/bin/arm-linux-androideabi-gcc

SYSR64 = $(NDK)/platforms/android-23/arch-arm64
GCC64 = $(NDK)/toolchains/aarch64-linux-android-4.9/prebuilt/darwin-x86_64/bin/aarch64-linux-android-gcc

all: speak32.so hello32 speak64.so hello64

speak32.so: speak.c
	$(GCC) -march=armv7-a --sysroot=$(SYSR) -llog -fPIC -shared speak.c -o speak32.so

hello32: hello.c
	$(GCC) -march=armv7-a --sysroot=$(SYSR) speak32.so -fPIC -pie hello.c -o hello32

speak64.so: speak.c
	$(GCC64) -march=armv8-a --sysroot=$(SYSR64) -llog -fPIC -shared speak.c -o speak64.so

hello64: hello.c
	$(GCC64) -march=armv8-a --sysroot=$(SYSR64) -llog speak64.so -fPIC -pie hello.c -o hello64

clean:
	rm speak32.so hello32 speak64.so hello64

