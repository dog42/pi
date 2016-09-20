#!/bin/bash
echo TROLOLOLOLOOOOOOO

if [ ! -f /home/$USER/.state  ]; then
        echo "1" > /home/$USER/.state
        echo "das erste mal"
        ./home/pi/.piconf/firstrun.sh
else
        echo "schon alt"
fi

# content of /etc/rc-local:
# wget https://github.com/D0gi/pi/archive/master.zip -O /home/pi/.master.zip
# unzip /home/pi/.master.zip -d /home/pi/.piconf
# rm /home/pi/.master.zip
# ./home/pi/.piconf/pi-master/go.sh
echo "cleanup"
sudo rm -rf home/pi/.master.zip /home/pi/.piconf