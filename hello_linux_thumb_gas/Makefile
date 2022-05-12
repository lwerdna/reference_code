all: hello

AS = arm-linux-gnueabi-as
LD = arm-linux-gnueabi-ld
OBJDUMP = arm-linux-gnueabi-objdump

hello: hello.o
	$(LD) hello.o -o hello

hello.o: hello.s
	 $(AS) -mthumb hello.s -o hello.o

dis:
	$(OBJDUMP) -d ./hello

clean:
	rm -f hello hello.o a.out
