all: hello_att hello_intel

hello_att.o: hello_att.S
	as ./hello_att.S -o hello_att.o

hello_att: hello_att.o
	ld hello_att.o -o hello_att

hello_intel.o: hello_intel.S
	as ./hello_intel.S -o hello_intel.o

hello_intel: hello_intel.o
	ld hello_intel.o -o hello_intel
