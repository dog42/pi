#!/bin/bash
echo TROLOLOLOLOOOOOOO

sudo apt install -y zsh
chsh -s $(which zsh)
sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
cp -r /home/pi/.piconf/pi-master/.oh-my-zsh home/pi/
echo "going to REBOOT"
sleep 10
sudo reboot

# content of /etc/rc-local:
# wget https://github.com/D0gi/pi/archive/master.zip -O /home/pi/.master.zip
# unzip /home/pi/.master.zip -d /home/pi/.piconf
# rm /home/pi/.master.zip
# ./home/pi/.piconf/pi-master/go.sh