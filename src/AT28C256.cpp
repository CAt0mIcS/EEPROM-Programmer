// #ifdef EEPROM_AT28C256
#include "EEPROMLibrary.h"
#include "ShiftRegister.h"
#include <Arduino.h>

#define WE_BAR_PIN 10
#define OE_BAR_PIN 11

#define IO0_PIN 2
#define IO7_PIN 9

void SetArduinoPinMode(int mode);
void SetDataPins(uint8_t data);

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
    // Serial.println("Write...: ");
    // Make sure EEPROM is not outputting data
    digitalWrite(OE_BAR_PIN, HIGH);

    WriteAddressToShiftRegisters(address);
    SetArduinoPinMode(OUTPUT);

    SetDataPins(data);
    // Serial.println();

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

    // Serial.println("Write-Paged...: ");
    // Make sure EEPROM is not outputting data
    digitalWrite(OE_BAR_PIN, HIGH);

    SetArduinoPinMode(OUTPUT);

    for (int i = 0; i < EEPROM_PAGE_SIZE; i++)
    {
        WriteAddressToShiftRegisters(startAddress + i);
        SetDataPins(data[i]);
        // Serial.println();

        // Initiate write cycle, address is latched at this point
        digitalWrite(WE_BAR_PIN, LOW);
        delayMicroseconds(1);

        // End write cycle, data is latched at this point
        digitalWrite(WE_BAR_PIN, HIGH);
        delayMicroseconds(1);
    }

    return true;
}

uint8_t ReadEEPROM(uint16_t address)
{
    // Serial.println("Read...: ");
    // Make sure EEPROM is not inputting data
    digitalWrite(WE_BAR_PIN, HIGH);

    SetArduinoPinMode(INPUT);
    WriteAddressToShiftRegisters(address);

    digitalWrite(OE_BAR_PIN, LOW);
    delayMicroseconds(1);

    byte b = 0;
    // byte bytes[8];
    for (int i = IO7_PIN; i >= IO0_PIN; i--)
    {
        int readState = digitalRead(i);
        // bytes[IO7_PIN - i] = readState;
        b = (b << 1) + readState;

        // Serial.print("Read ");
        // Serial.print(readState);
        // Serial.print(" on pin: ");
        // Serial.println(i);
    }

    // for (int i = 0; i < 8; i++)
    // {
    //     Serial.print(bytes[i]);
    // }
    // Serial.println();

    return b;
}

void SetArduinoPinMode(int mode)
{
    for (int i = IO0_PIN; i <= IO7_PIN; i++)
        pinMode(i, mode);
}

void SetDataPins(uint8_t data)
{
    for (int i = IO0_PIN; i <= IO7_PIN; i++)
    {
        digitalWrite(i, data & 1);
        // Serial.print(data & 1);
        data = data >> 1;
    }
}

// #endif