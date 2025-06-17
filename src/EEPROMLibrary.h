#ifndef EEPROM
#define EEPROM
#define EEPROM_SIZE 32768
#define EEPROM_PAGE_SIZE 64

#include <stdint.h>

void SetupEEPROM();
void WriteEEPROM(uint8_t data, uint16_t address);
bool WriteEEPROMPaged(uint8_t data[EEPROM_PAGE_SIZE], uint16_t startAddress);
uint8_t ReadEEPROM(uint16_t address);

#endif