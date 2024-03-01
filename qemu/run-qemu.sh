qemu-system-arm \
    -M raspi2 \
    -dtb qemu/bcm2836-rpi-2-b.dtb \
    -kernel out/baremetal.bin \
    -m 1G \
    -nographic
