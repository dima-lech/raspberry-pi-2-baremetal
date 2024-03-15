#/bin/bash

machine=`qemu-system-arm -machine help | grep raspi2 | cut -d' ' -f1`

set -x
qemu-system-arm \
    -M $machine \
    -dtb qemu/bcm2836-rpi-2-b.dtb \
    -kernel out/baremetal.bin \
    -m 1G \
    -nographic
