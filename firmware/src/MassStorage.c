/*
 * @brief USB Mass Storage Device Example
 *
 * @note
 * Copyright(C) NXP Semiconductors, 2012
 * Copyright(C) Dean Camera, 2011, 2012
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

#include "MassStorage.h"

#include "uartbridge.h"
#include "xprintf.h"
#include "cartucho.h"
#include "DataRam.h"
#include "loader.h"


/*****************************************************************************
 * Private types/enumerations/variables
 ****************************************************************************/

/** nxpUSBlib Mass Storage Class driver interface configuration and state information. This structure is
 *  passed to all Mass Storage Class driver functions, so that multiple instances of the same class
 *  within a device can be differentiated from one another.
 */
static USB_ClassInfo_MS_Device_t Disk_MS_Interface = {
	.Config = {
		.InterfaceNumber           = 0,

		.DataINEndpointNumber      = MASS_STORAGE_IN_EPNUM,
		.DataINEndpointSize        = MASS_STORAGE_IO_EPSIZE,
		.DataINEndpointDoubleBank  = false,

		.DataOUTEndpointNumber     = MASS_STORAGE_OUT_EPNUM,
		.DataOUTEndpointSize       = MASS_STORAGE_IO_EPSIZE,
		.DataOUTEndpointDoubleBank = false,

		.TotalLUNs                 = TOTAL_LUNS,
		.PortNumber = 0,
	},
};


/* HW set up function */
static void SetupHardware(void)
{
	Board_Init();

    UART0_Init(230400);
    NVIC_EnableIRQ(UART0_IRQn);
	xprintf("\n\n\nVectrexador\n");

#ifndef SERIALDEBUG	
    NVIC_DisableIRQ(UART0_IRQn);
	UART0_UnInit();
	VectrexBusInit();
#endif	

	USB_Init(Disk_MS_Interface.Config.PortNumber, USB_MODE_Device);
}

volatile int USBUnplugged = 0;
volatile int USBConnected = 0;

#define WITH_USB


/**
 *  @brief  Main program entry point
 *  @return Will never return
 *  @note   This routine contains the overall program flow, including initial
 *  setup of all components and the main program loop.
 */
int main(void)
{
	SetupHardware();
	iap_init();

#ifdef WITH_USB	

	xprintf("\nLet's see some usb stuff");
	
	int i;
	// initially expect USB connection
	for (i = 0; ; i++) {
		#if !defined(USB_DEVICE_ROM_DRIVER)
		MS_Device_USBTask(&Disk_MS_Interface);
		USB_USBTask(Disk_MS_Interface.Config.PortNumber, USB_MODE_Device);
		#endif
		//if (i > 350000 && !USBConnected) break;
		if (i > 600000 && !USBConnected) break;
	}
#endif
	// if USB is unplugged, serve the vectrex bus
	PrepareLoader(DataRam_GetScratchRAM());

	xprintf("\nLOADER.BIN ROMBase=%x\n", ROMBase);
	void *loader = ROMBase;
	SelectROM(DataRam_GetScratchRAM(), 1); 
	xprintf("1 ROMBase=%x\nServing...", ROMBase);
	ROMBase = loader;

    NVIC_DisableIRQ(UART0_IRQn);
	UART0_UnInit();		
	VectrexBusInit();


	//SelectROM(DataRam_GetScratchRAM(), 1); -- this works
	int romIndex = VectrexBusSlave();	
	//VectrexBusHold();

	SelectROM(DataRam_GetScratchRAM(), romIndex); 

	//VectrexBusUnhold();
	//VectrexNMI();
	for(;;)
		VectrexBusSlave();
}


// Connect/Disconnect events are bullshit

/**
 * @brief  Event handler for the library USB Connection event
 * @return Nothing
 */
void EVENT_USB_Device_Connect(void)
{
}

/**
 * @brief Event handler for the library USB Disconnection event
 * @return Nothing
 */
void EVENT_USB_Device_Disconnect(void)
{
}

/**
 * @brief Event handler for the library USB Configuration Changed event
 * @return Nothing
 */
void EVENT_USB_Device_ConfigurationChanged(void)
{
	bool ConfigSuccess = true;

	ConfigSuccess &= MS_Device_ConfigureEndpoints(&Disk_MS_Interface);
}

/**
 * @brief Event handler for the library USB Control Request reception event
 * @return	Nothing
 */
void EVENT_USB_Device_ControlRequest(void)
{
	USBConnected = 1;

	MS_Device_ProcessControlRequest(&Disk_MS_Interface);
}

/**
 * @brief Mass Storage class driver callback function
 * @return Nothing
 * @note   The reception of SCSI commands from the host, which must be processed
 */
bool CALLBACK_MS_Device_SCSICommandReceived(USB_ClassInfo_MS_Device_t *const MSInterfaceInfo)
{
	bool CommandSuccess;

	CommandSuccess = SCSI_DecodeSCSICommand(MSInterfaceInfo);
	return CommandSuccess;
}
