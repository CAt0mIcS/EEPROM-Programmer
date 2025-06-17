import os

# clear file
with open("src/Data.h", 'w'): pass

with open("src/BinaryGenerator/rom.bin", 'rb') as reader:
    with open("src/Data.h", 'w') as writer:
        byteStr = ""
        while (byte := reader.read(1)):
            byteStr += "0x" + byte.hex()
            byteStr += ", "
        
        writer.write(f"const byte bytes[32768] PROGMEM = {{{byteStr}}};")


os.system("C:/Users/Admin/.platformio/penv/Scripts/platformio.exe run --target upload")