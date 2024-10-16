#!/bin/bash
sudo killall openocd
sudo openocd -f interface/stlink.cfg -c "transport select hla_swd; set CHIPNAME at91samd21g18; set ENDIAN little; set CPUTAPID 0x0bc11477; source [find target/at91samdXX.cfg]" -c "init; halt" &
sleep 2
arm-none-eabi-gdb -ex="target extended-remote :3333" -ex="monitor reset init" build/SAMD-Demo.elf
