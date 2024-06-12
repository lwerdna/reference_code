TARGETS=hello-aarch64 hello-static-aarch64

all: $(TARGETS)

hello-aarch64:
	aarch64-linux-gnu-gcc hello.c -o hello-aarch64

hello-static-aarch64:
	aarch64-linux-gnu-gcc hello.c -static -o hello-static-aarch64

info:
	readelf -a ./hello-aarch64 | grep interpreter || true
	readelf -a ./hello-static-aarch64 | grep interpreter || true

qemu:
	qemu-aarch64 -L /usr/aarch64-linux-gnu ./hello-aarch64 || true
	qemu-aarch64 ./hello-static-aarch64 || true

clean:
	rm -f $(TARGETS)
