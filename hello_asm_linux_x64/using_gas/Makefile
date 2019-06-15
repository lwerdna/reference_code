all: hello_att

hello_att.o: hello_att.S
	as ./hello_att.S -o hello_att.o

hello_att: hello_att.o
	ld hello_att.o -o hello_att
