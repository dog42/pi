#!/bin/bash

function clean() {
	echo ">>>cleanup"
	sudo rm -rf /home/pi/.master.zip 
	sudo rm -rf /home/pi/.piconf
}

function blink() {
	echo "7" > /sys/class/gpio/export
	echo "out" > /sys/class/gpio/gpio7/direction
	for i in {1...11}
	do
		echo "0" > /sys/class/gpio/gpio7/value
		sleep 1
		echo "1" > /sys/class/gpio/gpio7/value
		sleep 1
	done
}

function sethostname(){
	ip=$(ip -4 a s eth0)
	regex1='((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])'
	if [[ $ip =~ $regex1 ]]
		then
		echo pi${BASH_REMATCH[3]} > /etc/hostname
		hostname pi${BASH_REMATCH[3]}
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
blink 