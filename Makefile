default: all

IMAGE_NAME = baremetal
CROSS_COMPILE=arm-none-eabi-
CFLAGS = -mcpu=cortex-a7 -fpic -ffreestanding -nostdlib -fno-builtin -Wall -Wextra -g -O0
OBJS = boot.o baremetal.o rpi_arch.o utils.o

OBJS_FILES = $(addprefix obj/,$(OBJS))
IMAGE_BIN_FILE = out/$(IMAGE_NAME).bin
IMAGE_ELF_FILE = out/$(IMAGE_NAME).elf
OBJDUMP_FILE = tmp/objdump.txt
READELF_FILE = tmp/readelf.txt

vpath %.c src
vpath %.s src

sd: all
	cp $(IMAGE_BIN_FILE) sd/

qemu: all 
	chmod +x qemu/run-qemu.sh
	qemu/run-qemu.sh

obj/:
	mkdir -p obj

out/:
	mkdir -p out

tmp/:
	mkdir -p tmp

all: obj/ out/ tmp/ $(IMAGE_BIN_FILE) $(OBJDUMP_FILE) $(READELF_FILE)
	@echo -n "\n"
	@ls -l out/*$(IMAGE_NAME)*

$(IMAGE_BIN_FILE): $(IMAGE_ELF_FILE)
	$(CROSS_COMPILE)objcopy $< -O binary $@

$(IMAGE_ELF_FILE): $(OBJS_FILES)
	$(CROSS_COMPILE)gcc $(CFLAGS) -T src/linker.ld -o $@ $^

$(OBJDUMP_FILE): $(IMAGE_ELF_FILE)
	$(CROSS_COMPILE)objdump -Sx $< > $@

$(READELF_FILE): $(IMAGE_ELF_FILE)
	$(CROSS_COMPILE)readelf -a $< > $@

obj/%.o: %.s
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@

obj/%.o: %.c
	$(CROSS_COMPILE)gcc $(CFLAGS) -c $< -o $@

clean:
	rm -f obj/* out/* tmp/*
	rm -f sd/$(IMAGE_NAME).bin
