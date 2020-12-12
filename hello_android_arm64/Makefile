all: hello

# get ndk-r21d toolchain at https://developer.android.com/ndk/downloads, unzip
# from android/build/tools run `./make_standalone_toolchain.py --arch arm64 --api 21 --install-dir /tmp/my-android-toolchain`
# now mv /tmp/my-android-toolchain ~/android_a64_api21_toolchain

BUILT_TOOLCHAIN = $(HOME)/android_a64_api21_toolchain
GCC = $(BUILT_TOOLCHAIN)/bin/aarch64-linux-android-gcc

hello: hello.c
	$(GCC) hello.c -o hello

clean:
	rm -f hello
