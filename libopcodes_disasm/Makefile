all: loctool

loctool: loctool.c
	gcc loctool.c -o loctool -lopcodes -lbfd -liberty -lz

clean:
	rm -f ./loctool
