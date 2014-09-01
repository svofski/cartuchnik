#  Project Name
PROJECT = vectrexador

DEFS=-DCORE_M3 -D__LPC17XX__ -D__LPC175X_6X__ -D__USE_CMSIS=CMSISv2p00_LPC17xx -DUSB_DEVICE_ONLY -DBOARD=BOARD_LPCXpressoBase_RevB
DEFS+=-DPROGMEMDISK
DEFS+=-DSERIALDEBUG
#USETTY=-DUSETTY
#TEST=-DTESTTTY
SERIAL=/dev/tty.SLAB_USBtoUART
BITRATE=230400

ARCH=-mthumb -mcpu=cortex-m3
OPTIMIZATION = -O0 -g 
#OPTIMIZATION = -Os -g 
#OPTIMIZATION = -O3 -g -save-temps -fverbose-asm
#OPTIMIZATION = -save-temps -fverbose-asm -Os -g -funroll-all-loops -fprefetch-loop-arrays
#OPTIMIZATION = -Os -g -funroll-all-loops

# Directory structure
SOURCEDIRS = \
roms \
src \
src/Lib \
externals/LPCUSBLib/Drivers/USB/Core \
externals/LPCUSBLib/Drivers/USB/Core/LPC \
externals/LPCUSBLib/Drivers/USB/Core/LPC/HCD \
externals/LPCUSBLib/Drivers/USB/Core/LPC/EHCI \
externals/LPCUSBLib/Drivers/USB/Core/LPC/OHCI \
externals/LPCUSBLib/Drivers/USB/Class/Device \
externals/LPCUSBLib/Drivers/USB/Core/HAL/LPC17XX \
externals/LPCUSBLib/Drivers/USB/Core/DCD/LPC17XX \
externals/lpc_core/lpc_board/boards_17xx_40xx/nxp_xpresso_1769 \
externals/lpc_core/lpc_chip/chip_17xx_40xx \
externals/lpc_core/lpc_ip \
externals/pff2a/src

INCLUDEDIRS = include \
src/Lib \
externals/LPCUSBLib \
externals/LPCUSBLib/Drivers/USB \
externals/lpc_core/lpc_chip/chip_17xx_40xx \
externals/lpc_core/lpc_chip/chip_common \
externals/lpc_core/lpc_board/board_common \
externals/lpc_core/lpc_board/boards_17xx_40xx/nxp_xpresso_1769 \
externals/lpc_core/lpc_ip \
externals/CMSIS/CMSIS/Include \
externals/pff2a/src

BUILDDIR = build
OUTDIR = bin

#  Compiler/Assembler/Linker/etc.
GCC = arm-none-eabi-gcc
GPP = arm-none-eabi-g++
LDSCRIPT = ldscript_rom_gnu.ld
OBJCOPY = arm-none-eabi-objcopy
SIZE = arm-none-eabi-size
MKDIR = mkdir
RM = rm -f
CP = cp

#  Compiler and linker flags
CFLAGS = -Wall -fno-common -std=gnu99 $(ARCH) $(OPTIMIZATION) $(DEFS) $(TEST) $(USETTY)
CFLAGS += $(foreach DIR, $(INCLUDEDIRS), -I$(DIR))
CPPFLAGS = $(CFLAGS) -fno-exceptions -fno-rtti
LDFLAGS = $(ARCH) $(OPTIMIZATION) -nostartfiles
LDFLAGS += -Wl,--gc-sections,-Map=$(BUILDDIR)/$(PROJECT).map -T$(LDSCRIPT) -u _sbrk
ASFLAGS = $(ARCH) -DRAM_MODE=0 -g
ASFLAGS += $(foreach DIR, $(INCLUDEDIRS), -I$(DIR))
LDLIBS = -lstdc++

# Source and object files
CFILES = $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.c))
CFILES += $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.cpp))
CFILES += $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.S))
OBJS = $(foreach CFILE, $(CFILES), $(BUILDDIR)/$(basename $(notdir $(CFILE))).o) 
HFILES = $(foreach DIR, $(INCLUDEDIRS), $(wildcard $(DIR)/*.h))

# Search path
VPATH = $(foreach DIR, $(SOURCEDIRS), $(strip $(DIR)):)

# Build rules
.PHONY: all clean 

all: $(BUILDDIR)/$(PROJECT).hex $(OUTDIR)/$(PROJECT).bin

burn: $(OUTDIR)/$(PROJECT).bin
	~/tmpsrc/lpc21isp/lpc21isp -bin $(OUTDIR)/$(PROJECT).bin $(SERIAL) $(BITRATE) 12000

burnterm: $(OUTDIR)/$(PROJECT).bin
	~/tmpsrc/lpc21isp/lpc21isp -term -bin $(OUTDIR)/$(PROJECT).bin $(SERIAL) $(BITRATE) 12000

clean:
	$(RM) $(OBJS)
	$(RM) $(BUILDDIR)/$(PROJECT).*
	$(RM) $(OUTDIR)/$(PROJECT).*

build/MassStorage.o: $(HFILES)

$(OUTDIR)/$(PROJECT).bin: $(BUILDDIR)/$(PROJECT).elf
	$(OBJCOPY) -O binary -j .text -j .data $(BUILDDIR)/$(PROJECT).elf $(OUTDIR)/$(PROJECT).bin
	$(CP) $(BUILDDIR)/$(PROJECT).map $(OUTDIR)/
	$(SIZE) $(BUILDDIR)/$(PROJECT).elf

$(BUILDDIR)/$(PROJECT).hex: $(BUILDDIR)/$(PROJECT).elf
	$(OBJCOPY) -R .stack -O ihex $(BUILDDIR)/$(PROJECT).elf $(BUILDDIR)/$(PROJECT).hex

$(BUILDDIR)/$(PROJECT).elf: $(OBJS) $(HFILES)
	$(GPP) $(LDFLAGS) -o $@ $(OBJS) $(LDLIBS)

$(BUILDDIR)/%.o: %.c
	$(GCC) $(CFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: %.cpp
	$(GPP) $(CPPFLAGS) -c -o $@ $<

$(BUILDDIR)/%.o: %.S
	$(GCC) $(ASFLAGS) -c -o $@ $<

$(OBJS): | $(BUILDDIR)

$(OUTDIR):
	$(MKDIR) $(OUTDIR)

$(BUILDDIR): | $(OUTDIR)
	$(MKDIR) $(BUILDDIR)
