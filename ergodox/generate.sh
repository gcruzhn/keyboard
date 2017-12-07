#!/bin/bash
cd ~/keyboard/ergodox/
rm -Rf ~/qmk_firmware/keyboards/ergodox/ez/keymaps/dvorak_spanish
cp -Rp dvorak_spanish ~/qmk_firmware/keyboards/ergodox/ez/keymaps/
cp -Rp make_layout.sh ~/qmk_firmware/keyboards/ergodox/ez
cd ~/qmk_firmware/keyboards/ergodox/ez
bash make_layout.sh
mv ~/qmk_firmware/ergodox_ez_dvorak_spanish.hex ~/keyboard/ergodox/dvorak_spanish
