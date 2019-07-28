#!/usr/bin/env python
# set an elf file's .e_machine to 0x29a
import sys
with open(sys.argv[1],'rb') as fp:
	fdata = fp.read()
if fdata[0:4] != b'\x7FELF':
	raise Exception('not an elf')
# 0x0000:
#typedef struct elf32_hdr{
#	unsigned char e_ident[EI_NIDENT]; // 16
# e_ident[0..4) is EI_MAG0, EI_MAG1, EI_MAG2, EI_MAG3
if fdata[0:4] != b'\x7FELF':
	raise Exception('not an elf')
# 0x0004:
# e_ident[4] is EI_CLASS {ELFCLASSNONE, ELFCLASS32, ELFCLASS64}
# 0x0005:
# e_ident[5] is EI_DATA {ELFDATANONE, ELFDATA2LSB (little-end), ELFDATA2MSB (big-end)}
# 0x0006:
# e_ident[6] is EI_VERSION {EV_NONE, EV_CURRENT}
# 0x0007:
# e_ident[7] is EI_OSABI {ELFOSABI_NONE, ELFOSABI_LINUX}
# 0x0008:
# e_ident[8] is EI_PAD (and extends 8 bits)
# 0x0010:
#	Elf32_Half e_type;
# 0x0012:
#	Elf32_Half e_machine;
if fdata[5] in (0,1): # none or little-end
	fdata = fdata[0:0x12] + b'\x9a\x02' + fdata[0x14:]
if fdata[5] == 2: # big-end
	fdata = fdata[0:0x12] + b'\x02\x9a' + fdata[0x14:]
#	...
with open(sys.argv[1],'wb') as fp:
	fp.write(fdata)
