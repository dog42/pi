#!/bin/bash

function clean() {
	echo ">>>cleanup"
	sudo rm -rf /home/pi/.master.zip 
	sudo rm -rf /home/pi/.piconf
}

function sethostname(){
	ip=$(ip -4 a s eth0)
	regex1='((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])'
	if [[ $ip =~ $regex1 ]]
		then
		echo pi${BASH_REMATCH[3]} >> /etc/hostname
		echo ">>>HOSTNAME SET TO: pi${BASH_REMATCH[3]}"
	fi
}


echo ">>>LETS START"
whoami
sethostname


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