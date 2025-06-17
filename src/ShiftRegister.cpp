#include "ShiftRegister.h"
#include <Arduino.h>

#define SER_ADDR_PIN D0
#define CLK_ADDR_PIN D5

#define SER_DATA_PIN D1
#define CLK_DATA_PIN D2

void PulseClock(int clock);

void SetupShiftRegisters()
{
    pinMode(SER_ADDR_PIN, OUTPUT);
    pinMode(CLK_ADDR_PIN, OUTPUT);

    pinMode(SER_DATA_PIN, OUTPUT);
    pinMode(CLK_DATA_PIN, OUTPUT);
}

void WriteAddressToShiftRegisters(uint16_t address, bool outputEEPROMContentsOnDatabus)
{
    for (int i = 0; i < 15; ++i)
    {
        digitalWrite(SER_ADDR_PIN, address & 1);
        PulseClock(CLK_ADDR_PIN);

        address = address >> 1;
    }

    // Use 16th bit of shift registers to control EEPROM's OE_BAR pin
    digitalWrite(SER_ADDR_PIN, !outputEEPROMContentsOnDatabus);
    PulseClock(CLK_ADDR_PIN);

    // One more clock pulse to output latched data
    PulseClock(CLK_ADDR_PIN);
}

void WriteDataToShiftRegister(uint8_t data)
{
    for (int i = 0; i < 8; i++)
    {
        digitalWrite(SER_DATA_PIN, data & 1);
        PulseClock(CLK_DATA_PIN);
    }

    // One more clock pulse to output latched data
    PulseClock(CLK_DATA_PIN);
}

void PulseClock(int clock)
{
    delayMicroseconds(1);
    digitalWrite(clock, HIGH);
    delayMicroseconds(1);
    digitalWrite(clock, LOW);
}