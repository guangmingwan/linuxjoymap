#!/bin/bash

system=$1
emulator=$2
path=$3

dir=`dirname "$path"`
rom=`basename "$path"`
ext="${rom##*.}"
filename=$(basename "$rom" ".${ext}")
keymap="${dir}/${filename}.keymap"
emuconf="/opt/retropie/configs/${system}/${emulator}.keymap"

if [ -f "${keymap}" ]; then

  echo "Keymap found, starting joymap.." >&2
  sudo /home/pi/joymap-0.4.2/loadmap "${keymap}" >&2 &

else

  echo "Game keymap not found, trying to find global emulator keymap.." >&2

  if [ -f "${emuconf}" ]; then
    echo "Global keymap found, starting joymap.." >&2
    sudo /home/pi/joymap-0.4.2/loadmap "${emuconf}" >&2 &
  fi

fi
