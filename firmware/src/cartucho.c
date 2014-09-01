#include "board.h"
#include "cartucho.h"

/* SCR pin definitions for pin muxing */
typedef struct {
	uint8_t pingrp;		/* Pin group */
	uint8_t pinnum;		/* Pin number */
	uint8_t pincfg;		/* Pin configuration for SCU */
	uint8_t funcnum;	/* Function number */
} PINMUX_GRP_T;

// Define Vectrex bus pins as GPIO, no pullups, input
static const PINMUX_GRP_T VectrexBus_Mux[] = {
	{ABUS_PORT,		ABUS_0,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_1,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_2,		IOCON_MODE_INACT, 	IOCON_FUNC0}, 	// shared with UART0
	{ABUS_PORT,		ABUS_3,		IOCON_MODE_INACT, 	IOCON_FUNC0}, 	// shared with UART0
	{ABUS_PORT,		ABUS_4,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_5,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_6,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_7,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_8,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_9,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_10,	IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_11,	IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_12,	IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_13,	IOCON_MODE_INACT, 	IOCON_FUNC0},
	{ABUS_PORT,		ABUS_14,	IOCON_MODE_INACT, 	IOCON_FUNC0},

	{DBUS_PORT,		DBUS_0,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{DBUS_PORT,		DBUS_1,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{DBUS_PORT,		DBUS_2,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{DBUS_PORT,		DBUS_3,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{DBUS_PORT,		DBUS_4,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{DBUS_PORT,		DBUS_5,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{DBUS_PORT,		DBUS_6,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{DBUS_PORT,		DBUS_7,		IOCON_MODE_INACT, 	IOCON_FUNC0},

	{CART_N_PORT,	CART_N,		IOCON_MODE_INACT,	IOCON_FUNC0},
	{CE_N_PORT,		CE_N,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{OE_N_PORT,		OE_N, 		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{RW_N_PORT, 	RW_N,		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{B6_PORT, 		B6, 		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{NMI_N_PORT, 	NMI_N, 		IOCON_MODE_INACT, 	IOCON_FUNC0},
	{HALT_N_PORT, 	HALT_N, 	IOCON_MODE_INACT, 	IOCON_FUNC0},
	{IRQ_N_PORT, 	IRQ_N,		IOCON_MODE_INACT, 	IOCON_FUNC0},

	{A2A3ENA_PORT,	A2A3ENA, 	IOCON_MODE_INACT, 	IOCON_FUNC0}	
};

// Init all Vectrex pins to default state
void VectrexBusInit(void)
{
	// set all pins to tri-state 
	for (int i = 0; i < (sizeof(VectrexBus_Mux) / sizeof(VectrexBus_Mux[0])); i++) {
		Chip_IOCON_PinMux(LPC_IOCON, VectrexBus_Mux[i].pingrp, VectrexBus_Mux[i].pinnum,
						  VectrexBus_Mux[i].pincfg, VectrexBus_Mux[i].funcnum);
		// false in lpcopenspeak means input, [geniusmeme]
		Chip_GPIO_WriteDirBit(LPC_GPIO, VectrexBus_Mux[i].pingrp, 
			VectrexBus_Mux[i].pinnum, false); //!		
		//Chip_GPIO_WritePortBit(LPC_GPIO, VectrexBus_Mux[i].pingrp, 
		//	VectrexBus_Mux[i].pinnum, true); //!
	}

	// A2A3ENA = 1, disable serial bootloader lines
	Chip_GPIO_WriteDirBit(LPC_GPIO, A2A3ENA_PORT, A2A3ENA, true);
	Chip_GPIO_WritePortBit(LPC_GPIO, A2A3ENA_PORT, A2A3ENA, true);
}


