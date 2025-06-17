rom = ("0xea," * 32768)

with open("rom.txt", "w") as out_file:
    out_file.write(rom)