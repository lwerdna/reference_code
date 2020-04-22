#!/usr/bin/env python3

import capstone

md = None
def disassemble(data):
	global md
	gen = md.disasm(data, 0)

	offset = 0
	for i in gen:
		addrstr = '%08X' % i.address
		bytestr = ' '.join(['%02X'%x for x in data[offset:offset+i.size]])
		asmstr = i.mnemonic + ' ' + i.op_str
		line = '%s: %s %s' % (addrstr, bytestr.ljust(48), asmstr)
		print(line)
		offset += i.size	

if __name__ == '__main__':
	md = capstone.Cs(capstone.CS_ARCH_X86, capstone.CS_MODE_64)

	# x64
	buf = [
		0x48,0x8D,0x35,0x1D,0x00,0x00,0x00,              # lea rsi, [rip + 0x1d]
		0xBA,0x0E,0x00,0x00,0x00,                        # mov edx, 0xe
		0xBF,0x01,0x00,0x00,0x00,                        # mov edi, 1
		0xB8,0x04,0x00,0x00,0x02,                        # mov eax, 0x2000004
		0x0F,0x05,                                       # syscall
		0xB8,0x01,0x00,0x00,0x02,                        # mov eax, 0x2000001
		0xBF,0x00,0x00,0x00,0x00,                        # mov edi, 0
		0x0F,0x05,                                       # syscall
	]
	buf = b''.join(map(lambda x: x.to_bytes(1, 'big'), buf))

	disassemble(buf)
