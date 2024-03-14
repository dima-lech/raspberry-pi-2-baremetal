default: all

IMAGE_NAME = baremetal
CROSS_COMPILE=arm-none-eabi-
CFLAGS = -mcpu=cortex-a7 -fpic -ffreestanding -nostdlib -fno-builtin -Wall -Wextra -g -O0 -Ishell/src -MMD
OBJS = boot.o baremetal.o rpi_arch.o utils.o dlsh.o gpu_test.o
LINKER_FILE = src/linker.ld
QEMU_SCRIPT = qemu/run-qemu.sh

OBJS_FILES = $(addprefix obj/,$(OBJS))
DEPS_FILES = $(OBJS_FILES:%.o=%.d)
IMAGE_BIN_FILE = out/$(IMAGE_NAME).bin
IMAGE_ELF_FILE = out/$(IMAGE_NAME).elf
OBJDUMP_FILE = tmp/objdump.txt
READELF_FILE = tmp/readelf.txt

GCC=$(CROSS_COMPILE)gcc
LD=$(CROSS_COMPILE)ld
OBJCOPY=$(CROSS_COMPILE)objcopy
OBJDUMP=$(CROSS_COMPILE)objdump
READELF=$(CROSS_COMPILE)readelf

vpath %.c src shell/src
vpath %.s src shell/src

sd: all
	cp $(IMAGE_BIN_FILE) sd/

qemu: all 
	@chmod +x $(QEMU_SCRIPT)
	$(QEMU_SCRIPT)

clean:
	rm -f obj/* out/* tmp/*
	rm -f sd/$(IMAGE_NAME).bin

obj/:
	@mkdir -p obj

out/:
	@mkdir -p out

tmp/:
	@mkdir -p tmp

all: obj/ out/ tmp/ $(IMAGE_BIN_FILE) $(OBJDUMP_FILE) $(READELF_FILE)
	@echo -n "\n"
	@ls -l out/*$(IMAGE_NAME)*

$(IMAGE_BIN_FILE): $(IMAGE_ELF_FILE)
	$(OBJCOPY) $< -O binary $@

$(IMAGE_ELF_FILE): $(OBJS_FILES)
	@echo " LD\t$@"
	@$(LD) -T $(LINKER_FILE) -o $@ $^

$(OBJDUMP_FILE): $(IMAGE_ELF_FILE)
	$(OBJDUMP) -Sx $< > $@

$(READELF_FILE): $(IMAGE_ELF_FILE)
	$(READELF) -a $< > $@


# Include all .d files
-include $(DEPS_FILES)

obj/%.o: %.s
	@echo " CC\t$<"
	@$(GCC) $(CFLAGS) -c $< -o $@

obj/%.o: %.c
	@echo " CC\t$<"
	@$(GCC) $(CFLAGS) -c $< -o $@


