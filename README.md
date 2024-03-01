# raspberry-pi-2-baremetal

This repository contains environment for building a bare-metal executable which runs on Raspberry Pi 2 B Arm core.
Execution can be emulated using QEMU.

## Build

Install Arm cross-compiler:
```
sudo apt install gcc-arm-none-eabi
```
Image is built using `make all`.


## QEMU

Install QEMU for ARM:
```
sudo apt install qemu-system-arm
```

*qemu* directory contains necessary files to run output image on QEMU.
`make qemu` can be used to build and run the image. Use *ctrl+a*, *x* to quit QEMU.


## RPi Hardware

An SD card is required to run on actual hardware, and its first partition has to be FAT32 (this is created by default using the [Raspberry Pi Imager](https://www.raspberrypi.com/software)).

At a minimum, the FAT32 partition has to include these files:
- **bootcode.bin** - first executed software
- **fixup.dat** - required for RAM initialization
- **start.elf** - reads *config.txt* (if present) and executes the *kernel* (*kernel7.img* by default)
- **config.txt** - optional, includes configuration parameters for startup
- ***kernel image***

Note that since first 4 steps involve running on the GPU (VPU / VideoCore IV), this sequence cannot be easily modified. The built ***kernel*** image is the first software to execute on the Arm core and so it is the starting point for out bare-metal image, which replaces the default kernel.

`make sd` can be used to copy required files to *sd* directory.


## Resources

### RPi Resources

- [Raspberry Pi - Firmware files](https://github.com/raspberrypi/firmware)
- [Raspberry Pi forums - boot sequence explanation](https://raspberrypi.stackexchange.com/questions/10442/what-is-the-boot-sequence)

### Additional Resources

- https://jsandler18.github.io
- https://github.com/s-matyukevich/raspberry-pi-os
- https://www.rpi4os.com/part1-bootstrapping
- https://wiki.osdev.org/Raspberry_Pi_Bare_Bones

