#pragma once

#include "vectrexbus.h"

extern int VectrexBusSlave(void);
void VectrexBusHold(void);
void VectrexBusUnhold(void);
void VectrexBusInit(void);
void VectrexNMI(void);

