#!/bin/bash
cd
git clone https://github.com/jackhumbert/qmk_firmware.git
git clone https://github.com/johgh/keyboard.git
cd ~/keyboard/ergodox/
./teensy_setup.sh
sudo apt-get install dfu-programmer
