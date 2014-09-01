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
* iap_driver.h
* Demonstrate basic capability of In-Application Programming feature
*
* by: Daniel Widyanto
*/

#ifndef IAP_DRIVER_H_
#define IAP_DRIVER_H_

/*
* IAP status codes
*/
typedef enum {
    CMD_SUCCESS = 0,
    INVALID_COMMAND,
    SRC_ADDR_ERROR,
    DST_ADDR_ERROR,
    SRC_ADDR_NOT_MAPPED,
    DST_ADDR_NOT_MAPPED,
    COUNT_ERROR,
    INVALID_SECTOR,
    SECTOR_NOT_BLANK,
    SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
    COMPARE_ERROR,
    BUSY,
} __e_iap_status;

/**
* Init IAP driver
* @return    0 for success
*/
int iap_init(void);

/**
* Erase flash sector(s)
*
* @param sector_start  The start of the sector to be erased
* @param sector_end    The end of the sector to be erased
*
* @return CMD_SUCCESS, BUSY, SECTOR_NOT_PREPARED_FOR_WRITE_OPERATION,
*         or INVALID_SECTOR
*/
int iap_erase_sector(unsigned int sector_start, unsigned int sector_end);

/**
* Prepare flash sector(s) for erase / writing
*
* @param sector_start  The start of the sector to be prepared
* @param sector_end    The end of the sector to be prepared
*
* @return CMD_SUCCESS, BUSY, or INVALID_SECTOR
*/
int iap_prepare_sector(unsigned int sector_start, unsigned int sector_end);

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
        unsigned int count);

#endif /* IAP_DRIVER_H_ */
