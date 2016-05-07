#!/bin/bash
cd ~/keyboard/ergodox/
rm -Rf ~/qmk_firmware/keyboard/ergodox_ez/keymaps/dvorak_spanish
cp -Rp dvorak_spanish ~/qmk_firmware/keyboard/ergodox_ez/keymaps/
cp -Rp make_layout.sh ~/qmk_firmware/keyboard/ergodox_ez
cd ~/qmk_firmware/keyboard/ergodox_ez
bash make_layout.sh
mv dvorak_spanish.hex ~/keyboard/ergodox/dvorak_spanish
