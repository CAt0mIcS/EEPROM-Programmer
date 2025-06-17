#include "ShiftRegister.h"
#include <Arduino.h>

#define SER_PIN A5
#define CLK_PIN A4

void SetupShiftRegister()
{
    pinMode(SER_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT);
}

void WriteAddressToShiftRegister(uint16_t address, bool outputEEPROMContentsOnDatabus)
{
    for (int i = 0; i < 14; ++i)
    {
        digitalWrite(SER_PIN, address & 1);
        delayMicroseconds(1);

        digitalWrite(CLK_PIN, HIGH);
        delayMicroseconds(1);
        digitalWrite(CLK_PIN, LOW);

        address = address >> 1;
    }

    // Use 16th bit of shift registers to control EEPROM's OE_BAR pin
    digitalWrite(SER_PIN, !outputEEPROMContentsOnDatabus);
    delayMicroseconds(1);
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(1);
    digitalWrite(CLK_PIN, LOW);

    delayMicroseconds(1);
    digitalWrite(CLK_PIN, HIGH);
    delayMicroseconds(1);
    digitalWrite(CLK_PIN, LOW);
}