TARGETS=hello-armhf hello-static-armhf hello-armel hello-static-armel

all: $(TARGETS)

hello-armhf:
	arm-linux-gnueabihf-gcc hello.c -o hello-armhf

hello-static-armhf:
	arm-linux-gnueabihf-gcc hello.c -static -o hello-static-armhf

hello-armel:
	arm-linux-gnueabi-gcc hello.c -o hello-armel

hello-static-armel:
	arm-linux-gnueabi-gcc hello.c -static -o hello-static-armel

info:
	readelf -a ./hello-armhf | grep interpreter || true
	readelf -a ./hello-static-armhf | grep interpreter || true
	readelf -a ./hello-armel | grep interpreter || true
	readelf -a ./hello-static-armel | grep interpreter || true

info2:
	objdump --section .interp --full-contents ./hello-armhf || true
	objdump --section .interp --full-contents ./hello-static-armhf || true
	objdump --section .interp --full-contents ./hello-armel || true
	objdump --section .interp --full-contents ./hello-static-armel || true

qemu:
	qemu-arm ./hello-armhf || true
	qemu-arm ./hello-static-armhf || true
	qemu-arm ./hello-armel || true
	qemu-arm ./hello-static-armel || true

clean:
	rm -f $(TARGETS)
