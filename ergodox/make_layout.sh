#!/bin/bash
make clean
MAPNAME=dvorak_spanish
make KEYMAP=$MAPNAME
mv ergodox_ez.hex "$MAPNAME.hex"
