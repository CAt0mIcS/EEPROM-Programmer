import os

# Script to generate main.cpp file which uploads all data in build/a.out to the EEPROM

# clear file
with open("src/main.cpp", 'w'): pass

with open("build/a.out", 'rb') as reader:
    with open("src/main.cpp", 'w') as writer:
        writer.write("""
#define EEPROM_AT28C256

#include <Arduino.h>
#include "EEPROMLibrary.h"

struct AddressDataPair
{
    uint8_t data;
    uint16_t address;
};

const AddressDataPair byteData[] = {"""
)
        # read all bytes
        byteList = reader.read()
        
        # Remove any area where 0x00
        step = 4
        byteAddrMap : dict[str, str] = dict()
        for i in range(0, len(byteList), step):
            # Ignore padding 0x00
            if byteList[i] == byteList[i + 1] == byteList[i + 2] == byteList[i + 3] == 0x00:
                pass
            else:
                for j in range(i, i + step):
                    byteAddrMap[hex(j)] = hex(byteList[j])
        
        for addr, byte in byteAddrMap.items():
            writer.write(f"{{ {byte}, {addr} }}, ")
        
        writer.write("};")

        writer.write(f"""
void setup()
{{
    Serial.begin(9600);
    SetupEEPROM();
    delay(100);
    for(int i = 0; i < {len(byteAddrMap.items())}; i++)
    {{
        AddressDataPair dt;
        memcpy_P(&dt, byteData + i, sizeof(AddressDataPair));
        WriteEEPROM(dt.data, dt.address);
        delay(10);
    }}
""")
        
        writer.write("    delay(100);")

        writer.write(f"""
    for(int i = 0; i < {len(byteAddrMap.items())}; i++)
    {{
        AddressDataPair dt;
        memcpy_P(&dt, byteData + i, sizeof(AddressDataPair));
        uint8_t foundData = ReadEEPROM(dt.address);
        if(foundData != dt.data)
        {{
            Serial.print("Invalid byte ");
            Serial.print(foundData);
            Serial.print(" written at ");
            Serial.print(dt.address);
            Serial.print(", expected ");
            Serial.println(dt.data);
        }}
    }}
""")

        writer.write("""    Serial.println("Write done");\n
}
void loop() 
{
}
""")


os.system("C:/Users/Admin/.platformio/penv/Scripts/platformio.exe run --target upload")