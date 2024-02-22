Build:

```
$ make
/Users/andrewl/Downloads/clang+llvm-17.0.1-arm64-apple-darwin22.0/bin/clang -ffreestanding -MMD -mno-red-zone -std=c11 -target x86_64-unknown-windows -c main.c -o main.o
/Users/andrewl/Downloads/clang+llvm-17.0.1-arm64-apple-darwin22.0/bin/ld.lld -flavor link -subsystem:efi_application -entry:efi_main main.o -out:bootx64.efi
```

Get qemu. Get open virtual machine firmware (OVFM) prebuilt for x86_64. My search turned up https://retrage.github.io/edk2-nightly/ and I got `DEBUGX64_OVFM.fd`.

Emulate:

```
qemu-system-x86_64 -drive if=pflash,format=raw,file=$HOME/Downloads/DEBUGX64_OVMF.fd -drive format=raw,file=fat:rw:. -net none
```

Then in the guest:

```
UEFI Interactive Shell v2.2
EDK II
UEFI v2.70 (EDK II, 0x00010000)
Mapping table
      FS0: Alias(s):HD0a1:;BLK1:
          PciRoot(0x0)/Pci(0x1,0x1)/Ata(0x0)/HD(1,MBR,0xBE1AFDFA,0x3F,0xFBFC1)
     BLK0: Alias(s):
          PciRoot(0x0)/Pci(0x1,0x1)/Ata(0x0)
     BLK2: Alias(s):
          PciRoot(0x0)/Pci(0x1,0x1)/Ata(0x0)
Press ESC in 4 seconds to skip startup.nsh or any other key to continue.
Shell> fs0:
FS0:\> ls
Directory of: FS0:\
02/20/2024  10:46               2,048  bootx64.efi
02/13/2024  11:37 <DIR>         8,192  efi
02/20/2024  10:46 <DIR>         8,192  guest_root
02/20/2024  10:46                 452  main.c
02/20/2024  10:46                 228  main.d
02/20/2024  10:46                 780  main.o
02/13/2024  11:27                 695  Makefile
02/20/2024  10:49                 774  README.md
          6 File(s)       4,977 bytes
          2 Dir(s)
FS0:\> boox64.efi
```

Which will clear the screen and print and loop:

```
Hello World!
```

## Addendum

Use ctrl+h instead of backspace when `-nographic`.

I don't know how to exit qemu. In graphical mode, just close window. Otherwise `kill` the pid or `pkill` the process name, like `pkill qemu-system-x86_64` or `kill` from gdb.

https://krinkinmu.github.io/2020/10/11/efi-getting-started.html

https://github.com/krinkinmu/efi
