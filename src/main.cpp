#define EEPROM_AT28C256

#include <Arduino.h>
#include "EEPROMLibrary.h"

#include "Data.h"

void setup()
{
	SetupEEPROM();

	Serial.begin(9600);

	byte bytes[64];
	for (int i = 0; i < 64; i++)
	{
		bytes[i] = i * 2;
	}

	delay(1000);
	if (!WriteEEPROMPaged(bytes, 0))
		Serial.println("Page write failed");

	for (int i = 0; i < 64; i++)
	{
		Serial.println(ReadEEPROM(i));
	}
}

void loop()
{
}
