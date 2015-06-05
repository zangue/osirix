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
OBJ = boot.o main.o
OBJ += gpio.o uart.o
OBJ += vsprintf.o printk.o panic.o

#
# Config
#
CC = arm-linux-gnueabihf-gcc
LD = arm-linux-gnueabihf-ld
OBJCOPY = arm-linux-gnueabihf-objcopy

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
	@echo "osirix.img"

.PHONY: clean
clean:
	@rm -f osirix.elf osirix.img
	@echo "CLEAN    osirix.elf"
	@echo "CLEAN    osirix.img"
	@rm -f $(OBJ)
	@echo "CLEAN    $(OBJ)"
	@rm -f $(DEP)
	@echo "CLEAN    $(DEP)"
