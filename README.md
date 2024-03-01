# raspberry-pi-2-baremetal

This repository contains environment for building a bare-metal executable which runs on Raspberry Pi 2 B ARM core.
Execution can be emulated using QEMU.

## QEMU

Install QEMU for ARM:
```
sudo apt install qemu-system-arm
```

*qemu* directory contains necessary files to run output image on QEMU.
`make qemu` can be used to build and run on QEMU. use *ctrl+a*, *x* to quit QEMU.


## SD Card

An SD card is required to run on actual hardware, and its first partition has to be FAT32 (this is created by default using the [Raspberry Pi Imager](https://www.raspberrypi.com/software)).

At a minimum, the FAT32 partition has to include these files:
- **bootcode.bin** - first executed software
- **fixup.dat** - required for RAM initialization
- **start.elf** - reads *config.txt* (if present) and executes the kernel (*kernel7.img* by default)
- **config.txt** - optional, includes configuration parameters for startup
- ***kernel image***

`make sd` can be used to copy required files to *sd* directory.






