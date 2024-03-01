default: all

IMAGE_NAME = baremetal
CROSS_COMPILE=arm-none-eabi-
CFLAGS = -mcpu=cortex-a7 -ffreestanding -nostdlib -fno-builtin -Wall -Wextra
OBJS = obj/boot.o obj/baremetal.o obj/rpi_arch.o

vpath %.c src
vpath %.s src

sd: all
	cp out/$(IMAGE_NAME).bin sd/

qemu: all 
	chmod +x qemu/run-qemu.sh
	qemu/run-qemu.sh

obj/:
	mkdir -p obj

out/:
	mkdir -p out

tmp/:
	mkdir -p tmp

all: obj/ out/ tmp/ out/$(IMAGE_NAME).bin tmp/objdump.txt tmp/readelf.txt
	ls -l out/

out/$(IMAGE_NAME).bin: out/$(IMAGE_NAME).elf
	$(CROSS_COMPILE)objcopy $< -O binary $@

out/$(IMAGE_NAME).elf: $(OBJS)
	$(CROSS_COMPILE)gcc $(CFLAGS) -T src/linker.ld -o $@ $^

tmp/objdump.txt: out/$(IMAGE_NAME).elf
	$(CROSS_COMPILE)objdump -S $< > $@

tmp/readelf.txt: out/$(IMAGE_NAME).elf
	$(CROSS_COMPILE)readelf -a $< > $@

obj/%.o: %.s
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@

obj/%.o: %.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/* out/* tmp/*
	rm -f sd/$(IMAGE_NAME).bin
