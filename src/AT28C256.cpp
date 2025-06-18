// #ifdef EEPROM_AT28C256
#include "EEPROMLibrary.h"
#include "ShiftRegister.h"
#include <Arduino.h>

#define WE_BAR_PIN D3
#define OE_BAR_PIN D4

void SetupEEPROM()
{
    SetupShiftRegisters();

    pinMode(WE_BAR_PIN, OUTPUT);
    pinMode(OE_BAR_PIN, OUTPUT);

    digitalWrite(WE_BAR_PIN, HIGH);
    digitalWrite(OE_BAR_PIN, LOW);
}

void WriteEEPROM(uint8_t data, uint16_t address)
{
    // Make sure EEPROM is not outputting data
    digitalWrite(OE_BAR_PIN, HIGH);

    WriteAddressToShiftRegisters(address);
    WriteDataToShiftRegister(data);

    // Initiate write cycle, address is latched at this point
    digitalWrite(WE_BAR_PIN, LOW);
    delayMicroseconds(1);

    // End write cycle, data is latched at this point
    digitalWrite(WE_BAR_PIN, HIGH);
    delayMicroseconds(1);
}

bool WriteEEPROMPaged(uint8_t data[EEPROM_PAGE_SIZE], uint16_t startAddress)
{
    // Check to see if startAddress starts at a page
    if (startAddress % EEPROM_PAGE_SIZE != 0)
        return false;

    // Make sure EEPROM is not outputting data
    digitalWrite(OE_BAR_PIN, HIGH);

    WriteAddressToShiftRegisters(startAddress);

    for (int i = 0; i < EEPROM_PAGE_SIZE; i++)
    {
        WriteDataToShiftRegister(data[i]);

        // Initiate write cycle, address is latched at this point
        digitalWrite(WE_BAR_PIN, LOW);
        delayMicroseconds(1);

        // End write cycle, data is latched at this point
        digitalWrite(WE_BAR_PIN, HIGH);
        delayMicroseconds(1);

        startAddress++;
        WriteAddressToShiftRegisters(startAddress);
    }

    return true;
}
// #endif