
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <stdlib.h>

#define PACKAGE "bfd"
#define PACKAGE_VERSION "2.30"
#include <bfd.h> // for bfd_arch_arm, etc. ~/downloads/binutils-2.30/bfd/bfd.h
#include <dis-asm.h> // for struct disassemble_info, etc. ~/downloads/binutils-2.30/include/dis-asm.h

#define DISASM_ADDRESS 0

int cb_fprintf(void *stream, const char *fmt, ...)
{
	va_list args;
	va_start(args, fmt);

	//printf("cb_fprintf(stream, \"%s\")\n", fmt);

	char *built_str = (char *)stream;
	char buf[1024];
	int rc = vsnprintf(buf, sizeof(buf)-1, fmt, args);
	va_end(args);
	strcat((char *)built_str, buf);
	return rc;
}

int disasm_libopcodes(uint8_t *data, int len, uint64_t addr, char *result)
{
	disassemble_info dinfo = {0};

	/* create disassemble_info */
	init_disassemble_info(&dinfo, NULL, NULL);
	/* enum bfd_flavour in <binutils_source>/bfd/bfd.h */
	dinfo.flavour = bfd_target_unknown_flavour;
	/* architecture/machine combies, see enum bfd_architecture in <binutils_source>/bfd/bfd.h */
	dinfo.arch = bfd_arch_mips;
	dinfo.mach = bfd_mach_mipsisa32r6;
	dinfo.endian = BFD_ENDIAN_BIG;
	disassemble_init_for_target(&dinfo); // reads dinfo.arch and populate extra stuff

	/* use the stream pointer as our private data
		(the buffer that fprintf() should append to) */
	dinfo.stream = (void *)result;

	/* create disassembler */
	disassembler_ftype disasm = disassembler(bfd_arch_mips, TRUE, bfd_mach_mipsisa32r6, NULL);
	if(!disasm) {
		printf("ERROR: disassembler() returned no function\n");
		return -1;
	}

	/* call disassembler
		will use callbacks in dinfo (like .read_memory_func, .print_addr_func, etc.)
		and the defaults are fine for this use case, see the defaults in a debugger
		or look at especially buffer_read_memory() in dis-buf.c for details */
	dinfo.fprintf_func = cb_fprintf;
	dinfo.octets_per_byte = 1;
	dinfo.buffer_vma = addr;
	dinfo.stop_vma = addr + len;
	/* source data */
	dinfo.buffer = data;
	dinfo.buffer_length = len;

	result[0] = '\0';
	disasm((bfd_vma)addr, &dinfo);

	return 0;
}

void assert(int result)
{
	if(!result) {
		printf("ERROR: assert() failed\n");
		exit(-1);
	}
}

int main(int ac, char **av)
{
	char result[1024];
	uint8_t data[128];
	int bytesn;

	if(ac<2) {
		printf("supply instruction bytes\n");
		return -1;
	}

	if(!strcmp(av[1],"test")) {
		assert(disasm_libopcodes((uint8_t *)"\x27\xbd\xff\xf0", 4, DISASM_ADDRESS, result) == 0);
		assert(!strcmp(result, "addiu\tsp,sp,-16"));
		assert(disasm_libopcodes((uint8_t *)"\xAF\xBE\x00\x0c", 4, DISASM_ADDRESS, result) == 0);
		assert(!strcmp(result, "sw\ts8,12(sp)"));
		assert(disasm_libopcodes((uint8_t *)"\x03\xa0\xf0\x25", 4, DISASM_ADDRESS, result) == 0);
		assert(!strcmp(result, "move\ts8,sp"));
		assert(disasm_libopcodes((uint8_t *)"\xaf\xc0\x00\x08", 4, DISASM_ADDRESS, result) == 0);
		assert(!strcmp(result, "sw\tzero,8(s8)"));
		exit(0);
	}

	printf("disassembling: ");
	bytesn = ac-1;
	for(int i=0; i<bytesn; ++i) {
		data[i] = strtoul(av[i+1], NULL, 16);
		printf("%02X ", data[i]);
	}
	printf("\n");

	if(disasm_libopcodes(data, bytesn, DISASM_ADDRESS, result)) {
		printf("ERROR: disasm_libopcodes()\n");
		return -1;
	}

	printf("%s\n", result);

	return 0;
}

