#/bin/bash

machine=`qemu-system-arm -machine help | grep raspi2 | cut -d' ' -f1`

set -x
qemu-system-arm \
    -M $machine \
    -dtb qemu/bcm2836-rpi-2-b.dtb \
    -device loader,file=out/baremetal.bin,addr=0x8000,force-raw=on,cpu-num=0 \
    -m 1G \
    -nographic
