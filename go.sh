#!/bin/bash

clean() {
	echo ">>>cleanup"
	sudo rm -rf /home/pi/.master.zip 
	sudo rm -rf /home/pi/.piconf
}

echo ">>>LETS START"
whoami

if [ ! -f /home/pi/.state  ]; then
	echo "1" > /home/pi/.state
	echo ">>>das erste mal"
	./home/pi/.piconf/pi-master/firstrun.sh
	clean
	echo ">>>going to reboot"
	sleep 6
	reboot
else
	echo ">>>schon alt"
fi

clean