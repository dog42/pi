#!/bin/bash

echo 'XKBMODEL="pc105"' > /etc/default/keyboard
echo 'XKBLAYOUT="de"' >> /etc/default/keyboard
echo 'XKBVARIANT=""' >> /etc/default/keyboard
echo 'XKBOPTIONS=""' >> /etc/default/keyboard

sudo su -c "echo  'de_DE.UTF-8 UTF-8' >> /etc/locale.gen"
sudo locale-gen "de_DE.UTF-8"
sudo update-locale LANG=de_DE.UTF-8
#echo 'LANG=de_DE.UTF-8' > /etc/default/locale
echo "keyboard set to de"

sudo apt-get update
#sudo apt-get -y upgrade
sudo apt install -y git zsh htop i2c-tools libi2c-dev python-smbus
sudo -u pi sh -c "$(curl -fsSL https://raw.github.com/robbyrussell/oh-my-zsh/master/tools/install.sh)"
cp -r /home/pi/.piconf/pi-master/.oh-my-zsh /home/pi/.piconf/pi-master/.zshrc /home/pi/.piconf/pi-master/.ssh home/pi/
chsh -s $(which zsh) pi

cd /home/pi
git clone git://git.drogon.net/wiringPi
cd /home/pi/wiringPi
git pull origin
./build



# #activate I2C
# sudo mknod /dev/i2c-0 c 89 0
# sudo mknod /dev/i2c-1 c 89 1
# sudo usermod -aG i2c pi
# sudo cat /etc/modprobe.d/raspi-blacklist.conf #(/etc/modprobe.d/fbdev-blacklist.conf)
# 	# blacklist spi and i2c by default (many users don't need them)
# 	# blacklist spi-bcm2708
# 	# blacklist i2c-bcm2708
# sudo nano /etc/modules 
# 	# i2c-dev
# sudo modprobe i2c-bcm2708
# sudo modprobe i2c_dev
# lsmod
# #ab Kernelversion 3.18
# sudo nano /boot/config.txt 
# 	# dtparam=i2c1=on
# 	# dtparam=i2c_arm=on
# sudo reboot

# while true;do for i in 48 49 4a 4b 4c 4d 4e 4f ;do printf "%s: " $i;printf "%d "  $(i2cget -y 1 0x$i 0x00);done; echo; sleep 1; done