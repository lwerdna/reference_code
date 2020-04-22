#ifdef OS_IS_WINDOWS
#include <Windows.h>
#else
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#endif

#include <string.h>
#include <stdint.h>
#include <fcntl.h>
#include <stdio.h>

/* macos "helloworld" shellcode tested on 10.15 Beta */
unsigned char shellcode[] = {
/* 00000000: */ 0x48,0x8D,0x35,0x1D,0x00,0x00,0x00,              /* lea rsi, [rip + 0x1d] */
/* 00000007: */ 0xBA,0x0E,0x00,0x00,0x00,                        /* mov edx, 0xe */
/* 0000000C: */ 0xBF,0x01,0x00,0x00,0x00,                        /* mov edi, 1 */
/* 00000011: */ 0xB8,0x04,0x00,0x00,0x02,                        /* mov eax, 0x2000004 */
/* 00000016: */ 0x0F,0x05,                                       /* syscall  */
/* 00000018: */ 0xB8,0x01,0x00,0x00,0x02,                        /* mov eax, 0x2000001 */
/* 0000001D: */ 0xBF,0x00,0x00,0x00,0x00,                        /* mov edi, 0 */
/* 00000022: */ 0x0F,0x05,                                       /* syscall  */
/* 00000024: */ 0x48,0x65,0x6C,                                  /* hello, world! */	
/* 00000027: */ 0x6C,
/* 00000028: */ 0x6F,
/* 00000029: */ 0x2C,0x20,
/* 0000002B: */ 0x77,0x6F,
/* 0000002D: */ 0x72,0x6C,
/* 0000002F: */ 0x64,0x21,0x0A
};

int main(int ac, char **av)
{
	int rc = -1;

	/* allocate executable buffer */
	uint8_t *buf_exec = NULL;
	#ifdef OS_IS_WINDOWS
	printf("VirtualAlloc()\n");
	buf_exec = (uint8_t *)VirtualAlloc(0, sizeof(shellcode), MEM_COMMIT|MEM_RESERVE, PAGE_READWRITE);
	if(!buf_exec) {
		printf("ERROR: VirtualAlloc()\n");
		return rc;
	}
	#else
	printf("mmap()\n");
	buf_exec = (uint8_t *)mmap(0, sizeof(shellcode), PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0);
	if(!buf_exec) {
		printf("ERROR: mmap()\n");
		return rc;
	}
	#endif

	/* copy to executable buffer */
	printf("memcpy()\n");
	memcpy(buf_exec, shellcode, sizeof(shellcode));

	#ifdef OS_IS_WINDOWS
	uint32_t oldProt;
	printf("VirtualProtect()\n");
	VirtualProtect(buf_exec, sizeof(shellcode), PAGE_EXECUTE_READWRITE, &oldProt);
	#else
	printf("mprotect()\n");
	mprotect(buf_exec, sizeof(shellcode), PROT_READ | PROT_EXEC);
	#endif

	/* execute the buffer */
	printf("calling %p\n", buf_exec);
	((void (*)(void))buf_exec)();
	printf("returned\n");

	rc = 0;
	cleanup:
	return rc;
}

