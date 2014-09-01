#include <stdint.h>
#include <string.h>
#include "pff.h"
#include "dataram.h"

// should be enough considering that a typical ROM is 4K
// we just can't fit more files in our flash disk
#define ROMTABLE_SIZE 4096

typedef struct _ROMEntry {
	char 		Name[16];
	uint32_t 	ROMBase;
	uint16_t	ROMSize;
} __attribute__((packed)) ROMEntry;

void ReadRomDirectory(uint8_t* scratch) 
{
	DIR root;
	FILINFO fno;
	uint16_t dummy;
	int result;

	ROMEntry* romtable = (ROMEntry*) (scratch + 32768 - ROMTABLE_SIZE);
	memset(romtable, 0, ROMTABLE_SIZE);

	// read directory
	result = pf_opendir(&root, "");
	if (result == FR_OK) {
		for(;;) {
			result = pf_readdir(&root, &fno);
			if (result != FR_OK || fno.fname[0] == 0) break;
			if ((fno.fattrib & (AM_DIR | AM_SYS | AM_HID)) != 0) continue;
			if (fno.fsize == 0) continue;
			if (strcmp(fno.fname, "LOADER.BIN") == 0) continue;

			strncpy(romtable->Name, fno.fname, sizeof(romtable->Name)-1);
			romtable->Name[strlen(romtable->Name)] = '\200';
			result = pf_open(fno.fname);
			pf_read(&dummy, 1, &dummy); 	// sets ROMBase to start of image
			romtable->ROMBase = (uint32_t) ROMBase;
			romtable->ROMSize = fno.fsize;
			romtable++;
		}
	}
}

void PrepareLoader(uint8_t* scratch) {
	FATFS fs;

	uint16_t dummy;
	int result;

	result = pf_mount(&fs);
	result = pf_open("LOADER.BIN");

	// trick pff into calculating the sector number for us
	// disk_readp() will call DataRam_SetROMBase()
	result = pf_read(&dummy, 1, &dummy);

	// Regular ROMs don't have to be in RAM, but the loader needs a file list
	memcpy(scratch, (const uint8_t*) ROMBase, 32768 - ROMTABLE_SIZE);

	ReadRomDirectory(scratch);

	// point current ROMBase to the RAM scratch area 
	ROMBase = scratch;
}
