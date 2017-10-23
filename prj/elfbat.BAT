@echo off 
D:\Keil_v5\ARM\ARMCC\bin\fromelf.exe --bin -o ./output/bin.bin ./Objects/pure.axf
D:\Keil_v5\ARM\ARMCC\bin\fromelf.exe --elf -o ./output/elf.elf  ./Objects/pure.axf
D:\Keil_v5\ARM\ARMCC\bin\fromelf.exe -c -o ./output/elf.dis  ./output/elf.elf
bin2hex_am8813.exe ./output/bin.bin ./output/main_rom.dat
D:\Keil_v5\ARM\ARMCC\bin\fromelf.exe --text -c -s --output=./output/list.lst ./Objects/pure.axf
copy .\output\main_rom.dat .\sim\main_rom.dat > nul
copy .\src\main.c .\sim\main.c > nul
copy .\output\list.lst .\sim\list.lst > nul