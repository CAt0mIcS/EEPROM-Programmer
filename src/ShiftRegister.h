#ifndef SHIFT_REGISTER
#define SHIFT_REGISTER

#include <stdint.h>

void SetupShiftRegisters();
void WriteAddressToShiftRegisters(uint16_t address);

#endif