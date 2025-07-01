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
                     
void setup()
{
    Serial.begin(9600);
    SetupEEPROM();
    delay(100);
"""
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
            writer.write(f"    WriteEEPROM({byte}, {addr});\n")
            writer.write("    delay(100);\n")
        
        writer.write("    delay(100);")
        
        for addr, byte in byteAddrMap.items():
            writer.write(f"""
    if(ReadEEPROM({addr}) != {byte}) {{
        Serial.print("Invalid byte written at {addr} (expected {byte} found ");
        Serial.println(ReadEEPROM({addr}));
        }}
""")

        writer.write("""    Serial.println("Write done");\n
}
void loop() 
{
}
""")


os.system("C:/Users/Admin/.platformio/penv/Scripts/platformio.exe run --target upload")