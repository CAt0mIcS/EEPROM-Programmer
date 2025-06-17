#ifndef SHIFT_REGISTER
#define SHIFT_REGISTER

#include <stdint.h>

void SetupShiftRegister();
void WriteAddressToShiftRegister(uint16_t address, bool outputEEPROMContentsOnDatabus);

#endif