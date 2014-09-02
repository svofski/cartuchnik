#pragma once

#define ABUS_PORT   0
#define ABUS_0  0
#define ABUS_1  1
#define ABUS_2  2
#define ABUS_3  3
#define ABUS_4  4
#define ABUS_5  5
#define ABUS_6  6
#define ABUS_7  7
#define ABUS_8  8
#define ABUS_9  9
#define ABUS_10 10
#define ABUS_11 11
                /* break */
#define ABUS_12 15
#define ABUS_13 16
#define ABUS_14 17

#define ABUS_ALLBV  0x38fff

#define DBUS_PORT   2
#define DBUS_0  0
#define DBUS_1  1
#define DBUS_2  2
#define DBUS_3  3
#define DBUS_4  4
#define DBUS_5  5
#define DBUS_6  6
#define DBUS_7  7

// CART_N: P0[18]
#define CART_N_PORT 0
#define CART_N      18

// CE_N: P0[24]
#define CE_N_PORT   0
#define CE_N        24

// OE_N: P0[25]
#define OE_N_PORT   0
#define OE_N        25

// RW_N: P0[26]
#define RW_N_PORT   0
#define RW_N        26

// B.6: P1[30] == A15, bank switching
#define B6_PORT     1
#define B6          30

// NMI_N: P0[21]
#define NMI_N_PORT  0
#define NMI_N       21

// HALT_N: P0[22]
#define HALT_N_PORT 0
#define HALT_N      22

// IRQ_N: P0[27]
#define IRQ_N_PORT  0
#define IRQ_N       27

// A2A3ENA: P2[13]
#define A2A3ENA_PORT    2
#define A2A3ENA         13

#define FIOX_X(X,Y)     (FIO ## X ## Y)
#define FIOPIN_XX(X)    FIOX_X(X,PIN)
#define FIODIR_XX(X)    FIOX_X(X,DIR)
#define FIOMASK_XX(X)   FIOX_X(X,MASK)

#define FIOPIN_ABUS     FIOPIN_XX(ABUS_PORT)
#define FIOMASK_ABUS    FIOMASK_XX(ABUS_PORT)
#define FIODIR_DBUS     FIODIR_XX(DBUS_PORT)
#define FIOPIN_DBUS     FIOPIN_XX(DBUS_PORT)
#define FIOMASK_DBUS    FIOMASK_XX(DBUS_PORT)
#define FIOPIN_B6       FIOPIN_XX(B6_PORT)
#define FIOMASK_B6      FIOMASK_XX(B6_PORT)