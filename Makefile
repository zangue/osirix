#
# Makefile
# ========
#
# make		-- Builds the Kernel.
# make all
#
# make clean	-- remove created files.
#

#
# source
#
LSCRIPT = linker.ld
OBJ = boot/boot.o boot/main.o
OBJ += drivers/gpio.o drivers/uart.o
OBJ += kernel/vsprintf.o kernel/printk.o kernel/panic.o

CROSSTOOL = arm-linux-gnueabihf

#
# Config
#
CC = $(CROSSTOOL)-gcc
LD = $(CROSSTOOL)-ld
OBJCOPY = $(CROSSTOOL)-objcopy

SFLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -c
CFLAGS = -mcpu=arm1176jzf-s -fpic -ffreestanding -std=gnu99 -O2 -Wall -Wextra -c
CPPFLAGS = -Iinclude
#LIBGCC := $(shell $(CC) -print-libgcc-file-name)

DEP = $(OBJ:.o=.d)

#
# Rules
#
.PHONY: all
all: osirix.img

-include $(DEP)

%.o: %.S
	@$(CC) $(CPPFLAGS) $(SFLAGS) -MMD -MP -o $@ $<
	@echo "AS    $@"

%.o: %.c
	@$(CC) $(CPPFLAGS) $(CFLAGS) -MMD -MP -o $@ $<
	@echo "CC    $@"

osirix.elf: $(LSCRIPT) $(OBJ)
	@$(LD) -T$(LSCRIPT) -o $@ $(OBJ) $(LIBGCC)
	@echo "LD    $@"

osirix.img: osirix.elf
	@$(OBJCOPY) $< -O binary $@
	@echo "osirix.img is ready."

.PHONY: clean
clean:
	@rm -f kernel.elf kernel.img
	@echo "CLEAN    osirix.elf"
	@echo "CLEAN    osirix.img"
	@rm -f $(OBJ)
	@echo "CLEAN    $(OBJ)"
	@rm -f $(DEP)
	@echo "CLEAN    $(DEP)"
