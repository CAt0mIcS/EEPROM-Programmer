#define EEPROM_AT28C256

#include <Arduino.h>
#include "EEPROMLibrary.h"

#include "Data.h"

void setup()
{
	SetupEEPROM();

	Serial.begin(9600);
	while (!Serial)
		;

	delay(1000);

	for (uint32_t address = 0; address < 32768; address += EEPROM_PAGE_SIZE)
	{
		byte pageBytes[EEPROM_PAGE_SIZE];
		memcpy_P(pageBytes, bytes + address, EEPROM_PAGE_SIZE);

		if (!WriteEEPROMPaged(pageBytes, address))
			Serial.println("Page write failed");
	}
}

void loop()
{
}
