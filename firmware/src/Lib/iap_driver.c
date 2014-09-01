/*
* Copyright (c) 2010, NXP Semiconductors N.V.
* All rights reserved.
*
* Redistribution and use in source and binary forms, with or without
* modification, are permitted provided that the following conditions are met:
*   * Redistributions of source code must retain the above copyright
*     notice, this list of conditions and the following disclaimer.
*   * Redistributions in binary form must reproduce the above copyright
*     notice, this list of conditions and the following disclaimer in the
*     documentation and/or other materials provided with the distribution.
*   * Neither the name of the NXP Semiconductors N.V. nor the
*     names of its contributors may be used to endorse or promote products
*     derived from this software without specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND  CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR IMPLIED  WARRANTIES,  INCLUDING,  BUT NOT LIMITED TO, THE
* IMPLIED WARRANTIES OF  MERCHANTABILITY  AND FITNESS FOR A PARTICULAR PURPOSE
* ARE DISCLAIMED.  IN NO EVENT SHALL NXP Semiconductors N.V. BE LIABLE FOR ANY
* DIRECT, INDIRECT,  INCIDENTAL,  SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
* (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
* LOSS  OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
* ON ANY  THEORY  OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
* (INCLUDING NEGLIGENCE OR  OTHERWISE)  ARISING  IN  ANY WAY OUT OF THE USE OF
* THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/*
* iap_driver.c
* Demonstrate basic capability of In-Application Programming feature
*
* by: Daniel Widyanto
*/

#include "board.h"
#include "iap_driver.h"

/*
* The IAP funtion address in LPC11xx ROM
*/
#define IAP_ADDRESS            0x1FFF1FF1

/*
* Command codes for IAP
*/
#define PREPARE_SECTOR      50
#define COPY_RAM_TO_FLASH   51
#define ERASE_SECTOR        52
#define BLANK_CHECK_SECTOR  53
#define READ_PART_ID        54
#define READ_BOOT_CODE_REV  55
#define COMPARE             56
#define REINVOKE_ISP        57
#define READ_UID            58

typedef unsigned int (*IAP)(unsigned int[], unsigned int[]);
static const IAP iap_entry = (IAP) IAP_ADDRESS;

/*---------------------------------------------------------------------------
* Public functions
*/

/**
* Init IAP driver
* @return    0 for success
*/
int iap_init(void) {
    /* Need to update 'SystemCoreClock' according to the current clock settings
     * It's needed as IAP parameter
     */
    SystemCoreClockUpdate();
    return 0;
}

/**
* Erase flash sector(s)
*
* @param sector_start  The start of the sector to be erased
* @param sector_end    The end of the sector to be erased
*
* @return CMD_SUCCESS, BUSY, SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
*         or INVALID_SECTOR
*/
int iap_erase_sector(unsigned int sector_start, unsigned int sector_end) {
    unsigned int command[5];
    unsigned int result[4];

    command[0] = ERASE_SECTOR;
    command[1] = (unsigned int) sector_start;
    command[2] = (unsigned int) sector_end;
    command[3] = SystemCoreClock / 1000;
    iap_entry(command, result);

    return (int) result[0];
}

/**
* Prepare flash sector(s) for erase / writing
*
* @param sector_start  The start of the sector to be prepared
* @param sector_end    The end of the sector to be prepared
*
* @return CMD_SUCCESS, BUSY, or INVALID_SECTOR
*/
int iap_prepare_sector(unsigned int sector_start, unsigned int sector_end) {
    unsigned int command[5];
    unsigned int result[4];

    command[0] = PREPARE_SECTOR;
    command[1] = (unsigned int) sector_start;
    command[2] = (unsigned int) sector_end;
    iap_entry(command, result);

    return (int) result[0];
}

/**
* Copy RAM contents into flash
*
* @param ram_address    RAM address to be copied
*                       It should be in word boundary
* @param flash_address  Flash address where the contents are to be copied
*                       It should be within 256bytes boundary
* @param count          Number of data to be copied (in bytes)
*                       The options: 256, 512, 1024, 4096
*
* @return CMD_SUCCESS, BUSY, or INVALID_SECTOR
*/
int iap_copy_ram_to_flash(void* ram_address, void* flash_address,
        unsigned int count) {
    unsigned int command[5];
    unsigned int result[4];

    command[0] = COPY_RAM_TO_FLASH;
    command[1] = (unsigned int) flash_address;
    command[2] = (unsigned int) ram_address;
    command[3] = count;
    command[4] = SystemCoreClock / 1000;
    iap_entry(command, result);

    return (int) result[0];
}

