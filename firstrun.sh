#!/bin/bash

echo 'XKBMODEL="pc105"\nXKBLAYOUT="de"\nXKBVARIANT=""\nXKBOPTIONS=""' > /etc/default/keyboard
echo "keyboard set to de"

sudo apt install -y zsh
chsh -s $(which zsh)
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
cp -r /home/pi/.piconf/pi-master/.oh-my-zsh home/pi/