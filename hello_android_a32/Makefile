all: hello

# get ndk-r21d toolchain at https://developer.android.com/ndk/downloads, unzip
# from android/build/tools run `./make_standalone_toolchain.py --arch arm --api 21 --install-dir /tmp/my-android-toolchain`
# now mv /tmp/my-android-toolchain ~/android_a32_api21_toolchain

BUILT_TOOLCHAIN = $(HOME)/android_arm_api21_toolchain
GCC = $(BUILT_TOOLCHAIN)/bin/arm-linux-androideabi-gcc

hello: hello.c
	$(GCC) hello.c -o hello

clean:
	rm -f hello
