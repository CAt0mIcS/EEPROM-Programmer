#include "ShiftRegister.h"
#include <Arduino.h>

#define SER_PIN 12
#define CLK_PIN 13

void PulseClock(int clock);

void SetupShiftRegisters()
{
    pinMode(SER_PIN, OUTPUT);
    pinMode(CLK_PIN, OUTPUT);
}

void WriteAddressToShiftRegisters(uint16_t address)
{
    for (int i = 0; i < 16; ++i)
    {
        digitalWrite(SER_PIN, address & 1);
        PulseClock(CLK_PIN);

        address = address >> 1;
    }

    // One more clock pulse to output latched data
    PulseClock(CLK_PIN);
}

void PulseClock(int clock)
{
    delayMicroseconds(1);
    digitalWrite(clock, HIGH);
    delayMicroseconds(1);
    digitalWrite(clock, LOW);
    delayMicroseconds(1);
}