Assemble an arm binary on a x86/64 machine. Run with qemu.

sudo apt-get install gcc-arm-linux-gnueabi
sudo apt-get install binutils-arm-linux-gnueabi
sudo apt-get install qemu-user
make
qemu-arm ./hello
