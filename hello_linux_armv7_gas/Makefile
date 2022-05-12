all: hello

AS = arm-linux-gnueabi-as
LD = arm-linux-gnueabi-ld

hello: hello.o
	# see `ld -V` for other -m options
	$(LD) hello.o -o hello

hello.o: hello.s
	 $(AS) hello.s -o hello.o

clean:
	rm -f hello hello.o a.out
