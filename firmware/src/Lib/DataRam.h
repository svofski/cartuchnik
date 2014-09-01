/*
 * @brief Header file for DataflashManager.c
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * All rights reserved.
 *
 * @par
 * Software that is described herein is for illustrative purposes only
 * which provides customers with programming information regarding the
 * LPC products.  This software is supplied "AS IS" without any warranties of
 * any kind, and NXP Semiconductors and its licensor disclaim any and
 * all warranties, express or implied, including all implied warranties of
 * merchantability, fitness for a particular purpose and non-infringement of
 * intellectual property rights.  NXP Semiconductors assumes no responsibility
 * or liability for the use of the software, conveys no license or rights under any
 * patent, copyright, mask work right, or any other intellectual property rights in
 * or to any products. NXP Semiconductors reserves the right to make changes
 * in the software without notification. NXP Semiconductors also makes no
 * representation or warranty that such application will be suitable for the
 * specified use without further testing or modification.
 *
 * @par
 * Permission to use, copy, modify, and distribute this software and its
 * documentation is hereby granted, under NXP Semiconductors' and its
 * licensor's relevant copyrights in the software, without fee, provided that it
 * is used in conjunction with NXP Semiconductors microcontrollers.  This
 * copyright, permission, and disclaimer notice must appear in all copies of
 * this code.
 */

/** @file
 *  Header file for DataflashManager.c.
 */

#ifndef __DATARAM_H_
#define __DATARAM_H_

#include <stdint.h>

#define DATA_RAM_BLOCK_SIZE             0x200

/** Start address and size of RAM area which used for disk image */
#define UTILITY_AREA_SECTORS 			4
#define UTILITY_AREA_RAM_SIZE			((DATA_RAM_BLOCK_SIZE)*(UTILITY_AREA_SECTORS))
#define DATA_RAM_USER_SIZE				0x8000
#define DATA_RAM_PHYSICAL_SIZE          (DATA_RAM_USER_SIZE + UTILITY_AREA_RAM_SIZE)
#define DATA_RAM_VIRTUAL_SIZE           DATA_RAM_PHYSICAL_SIZE

#ifdef PROGMEMDISK
#define FLASH_DISK_SIZE 				(384*1024)
#define FLASH_SECTOR_BASE				18
#define FLASH_SECTOR_COUNT				(29-18)
#define FLASH_SECTOR_SIZE				32768
#endif

/** Total number of bytes of the storage medium, comprised of one or more Dataflash ICs. */
#ifdef PROGMEMDISK
#define VIRTUAL_MEMORY_BYTES                FLASH_DISK_SIZE
#define VIRTUAL_MEMORY_BLOCK_SIZE           DATA_RAM_BLOCK_SIZE
#define VIRTUAL_MEMORY_BLOCKS               (VIRTUAL_MEMORY_BYTES / VIRTUAL_MEMORY_BLOCK_SIZE)
#else
#define VIRTUAL_MEMORY_BYTES                DATA_RAM_VIRTUAL_SIZE

/** Block size of the device. This is kept at 512 to remain compatible with the OS despite the underlying
 *  storage media (Dataflash) using a different native block size. Do not change this value.
 */
#define VIRTUAL_MEMORY_BLOCK_SIZE           512

/** Total number of blocks of the virtual memory for reporting to the host as the device's total capacity. Do not
 *  change this value; change VIRTUAL_MEMORY_BYTES instead to alter the media size.
 */
#define VIRTUAL_MEMORY_BLOCKS               (VIRTUAL_MEMORY_BYTES / VIRTUAL_MEMORY_BLOCK_SIZE)
#endif

uint32_t MassStorage_GetAddressInImage(uint32_t startblock, uint16_t requestblocks, uint16_t *availableblocks);
uint32_t MassStorage_GetAddressInFlash(uint32_t startblock, uint16_t requestblocks, uint16_t *availableblocks);


void MassStorage_BeginWritingBlocks(int first_block);
uint8_t* MassStorage_BeforeWritingBlock(int block);
void MassStorage_WriteBlock(int block);
void MassStorage_FinishWritingBlocks();

void DataRam_Initialize(void);

extern volatile uint8_t* ROMBase;

void DataRam_SetROMBase(uint8_t* rom);
uint8_t* DataRam_GetScratchRAM();

#endif /* __DATARAM_H_ */
