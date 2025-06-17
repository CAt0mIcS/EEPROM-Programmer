import os

# clear file
with open("src/Data.h", 'w'): pass

arrayLength : int = 16384

with open("src/BinaryGenerator/rom.bin", 'rb') as reader:
    with open("src/Data.h", 'w') as writer:
        writer.write("#ifndef DATA_H\n#define DATA_H\n")
        writer.write(f"#define DATA_ARRAY_SIZE {arrayLength}\n")
        writer.write("#include <Arduino.h>\n")

        for i in range(0, int(32768 / arrayLength)):
            byteStr = ""
            for j in range(0, arrayLength):
                byte = reader.read(1)
                byteStr += "0x" + byte.hex()
                byteStr += ", "
            
            writer.write(f"const byte bytes{i}[{arrayLength}] PROGMEM = {{{byteStr}}};\n")
        
        writer.write("#endif")


os.system("C:/Users/Admin/.platformio/penv/Scripts/platformio.exe run --target upload")