# sudo apt-get install binutils-aarch64-linux-gnu

all: mte-linux-aarch64.elf

mte-linux-aarch64.elf: main.o
	/usr/aarch64-linux-gnu/bin/ld -s -o mte-linux-aarch64.elf main.o

main.o: main.S
	/usr/aarch64-linux-gnu/bin/as main.S -o main.o

clean:
	rm main.o mte-linux-aarch64.elf
