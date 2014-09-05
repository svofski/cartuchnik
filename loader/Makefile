PROJECT = loader
OUTDIR = build
SOURCEDIRS = src

CROSS=/opt/local/gccvectrex/bin
CC=$(CROSS)/m6809-unknown-none-gcc
LD=$(CC)
AS=$(CC)

#OPTIMIZE=-O0
OPTIMIZE=-Os
#OPTIMIZE=-freorder-blocks -fmove-loop-invariants
#include optimizations.s.inc

CFLAGS=-std=c99 -fomit-frame-pointer $(OPTIMIZE) # -save-temps
LDFLAGS=-L/opt/local/gccvectrex/m6809-unknown-none/lib -lc -Wl,-Tfaketable -Wl,0x7000

CRT0 = crt0

SRCFILES = $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.c))
SRCFILES += $(foreach DIR, $(SOURCEDIRS), $(wildcard $(DIR)/*.S))
OBJS = $(foreach SRCFILE, $(SRCFILES), $(OUTDIR)/$(basename $(notdir $(SRCFILE))).o) 

OFILES = $(CRT0).o $(OBJS)

VPATH = $(foreach DIR, $(SOURCEDIRS), $(strip $(DIR)):)

all:	$(OUTDIR) $(OUTDIR)/$(PROJECT).bin

clean:	
	rm -f $(OUTDIR)/*

$(OUTDIR):
	mkdir -p $(OUTDIR)

$(OUTDIR)/$(PROJECT).bin:	$(OUTDIR)/$(PROJECT).s19
	srec_cat -Disable_Sequence_Warnings $? -Output $@.64k -Binary 
	dd if=$@.64k of=$@ bs=16384 count=1

$(OUTDIR)/$(PROJECT).s19:	$(OUTDIR)/$(OFILES)
	$(LD) $(LDFLAGS) $(OUTDIR)/$(OFILES) -o $@ -Wl,--map

$(OUTDIR)/%.o:	%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(OUTDIR)/%.o:	%.S
	$(AS) $(CFLAGS) -c -o $@ $<

$(OUTDIR)/%.s:	%.c
	$(CC) $(CFLAGS) -S -fverbose-asm -o $@ $<

