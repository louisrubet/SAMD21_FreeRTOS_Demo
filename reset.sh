#!/bin/bash
cd /home/louis/Development/aiotrust/firmware/delivery/
sudo killall openocd
sudo openocd -f interface/stlink.cfg -c "transport select hla_swd; set CHIPNAME at91samd21g18; set ENDIAN little; set CPUTAPID 0x0bc11477; source [find target/at91samdXX.cfg]" -c "init; halt" -c "at91samd chip-erase" -c "program master-bootloader.bin" -c "reset; exit"
