#!/usr/bin/env python

import os
import sys

with open(sys.argv[1], 'rb+') as fp:
    blob = fp.read()
    offset = blob.find(b'\xCC\xCC\xCC\xCC')

    found = True
    if offset == -1:
        found = False
    if blob[offset-1] == 0xCC or blob[offset+4] == 0xCC: # ignore large runs of 0xCC filler
        found = False

    if found:
        print(f'marker found at offset 0x{offset:X}')
        fp.seek(offset, os.SEEK_SET)
        payload = b'\x90\x90\xeb\xfe' # nop, nop, jump $
        print(f'writing {payload} to 0x{offset:X}')
        fp.write(payload)
        print('DONE')
    else:
        print('ERROR: marker not found')

