#!/bin/bash

echo 'XKBMODEL="pc105"' > /etc/default/keyboard
echo 'XKBLAYOUT="de"' >> /etc/default/keyboard
echo 'XKBVARIANT=""' >> /etc/default/keyboard
echo 'XKBOPTIONS=""' >> /etc/default/keyboard
echo "keyboard set to de"

sudo apt-get update
sudo apt install -y git zsh
chsh -s $(which zsh)
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
cp -r /home/pi/.piconf/pi-master/.oh-my-zsh home/pi/