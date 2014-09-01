/*-----------------------------------------------------------------------*/
/* Low level disk I/O module skeleton for Petit FatFs (C)ChaN, 2009      */
/*-----------------------------------------------------------------------*/


#include <string.h>
#include "dataram.h"
#include "diskio.h"

/*-----------------------------------------------------------------------*/
/* Initialize Disk Drive                                                 */
/*-----------------------------------------------------------------------*/

DSTATUS disk_initialize (void)
{
	return 0;
}

/*-----------------------------------------------------------------------*/
/* Read Partial Sector                                                   */
/*-----------------------------------------------------------------------*/

DRESULT disk_readp (
	BYTE* dest,			/* Pointer to the destination object */
	DWORD sector,		/* Sector number (LBA) */
	WORD sofs,			/* Offset in the sector */
	WORD count			/* Byte count (bit15:destination) */
)
{
	uint16_t availablebollocks;
	uint8_t *data = (uint8_t *) MassStorage_GetAddressInImage(sector, 1, &availablebollocks);
	DataRam_SetROMBase(data);
	memcpy(dest, data + sofs, count);

	return 0;
}



/*-----------------------------------------------------------------------*/
/* Write Partial Sector                                                  */
/*-----------------------------------------------------------------------*/

DRESULT disk_writep (
	const BYTE* buff,		/* Pointer to the data to be written, NULL:Initiate/Finalize write operation */
	DWORD sc				/* Sector number (LBA) or Number of bytes to send */
)
{
	DRESULT res = STA_NOINIT;


	if (!buff) {
		if (sc) {

			// Initiate write process

		} else {

			// Finalize write process

		}
	} else {

		// Send data to the disk

	}

	return res;
}

