Get kernel release:
$ uname --kernel-release
6.5.0-21-generic

Use that to ensure the path exists:
$ ls /lib/modules/6.5.0-21-generic/build
...

Now call make, with option to switch to that directory and read its Makefile:
$ make -C /lib/modules/6.5.0-21-generic/build M=`pwd` modules

Insert module into kernel:
$ insmod ./hello.ko
$ lsmod
Module                  Size  Used by
hello                  12288  0

$ dmesg
[183839.628857] hello: loading out-of-tree module taints kernel.
[183839.628868] hello: module verification failed: signature and/or required key missing - tainting kernel
[183839.631739] Hello world 1.


Find other targets:
$ make -C /lib/modules/6.5.0-21-generic/build help
Like:
$ make -C /lib/modules/6.5.0-21-generic/build M=`pwd` clean

For buildroot, initiate a linux kernel build.
If there's been a previous build, you can trigger a new one by:
`make linux-menuconfig` from buildroot root and toggle some option then `make`.
Read the CROSS_COMPILE path and use it:

$ ARCH=arm CROSS_COMPILE="/home/andrewl/Downloads/buildroot-2013.11/output/host/usr/bin/arm-buildroot-linux-uclibcgnueabi-" make -C /home/andrewl/Downloads/buildroot-2013.11/output/build/linux-3.10 M=`pwd` modules
