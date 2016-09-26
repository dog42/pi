#!/bin/bash
echo LETS START
whoamicd 

if [ ! -f /home/pi/.state  ]; then
        echo "1" > /home/pi/.state
        echo "das erste mal"
        ./home/pi/.piconf/pi-master/firstrun.sh
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