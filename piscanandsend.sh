#!/bin/bash
ips=''
pis=''
function greth(){
        for x in `/sbin/ifconfig |egrep -v "^ "| awk '{print $1}'`
        do
                iface=${x//:}
                if [[ $(echo "$iface" | grep -o "^e") ]]; then
                        echo $(ip -4 a s ${x//:} up | grep -Eo '((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])' | grep -m1 '.*')
                fi
        done
}

function slowscan () {
        if (( $# >= 2 ))
        then
                echo "usage: $FUNCNAME [ip[/mask]]"
                echo "example: $FUNCNAME"
                echo "example: $FUNCNAME 192.168.0.1/24"
        fi
        if (( $# == 0 ))
        then
                nmap -T3 -sP --max-hostgroup 50 --min-rate 100000 `greth`/24
        else
                nmap -T3 -sP --max-hostgroup 50 --min-rate 100000 "$1"
        fi
}

function cleanscan (){
  regex1='((for\s)(\S+)\.lan\s\()?(((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9]))'
  scan=$(slowscan)
  i=0
  IFS=$'\n' #ZEILWEISE LESEN
  for f in $scan
  do
    if [[ $f =~ $regex1 ]]
    then
      echo "${BASH_REMATCH[4]} ${BASH_REMATCH[3]}"
      ips[i++]="${BASH_REMATCH[4]} ${BASH_REMATCH[3]}"
    fi 
  done
  IFS=''
}

function getpis(){
  #regex2='\s(pi[0-9]{1,2})'
  regex2='(((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9]))\s(pi[0-9]{1,3}|raspberrypi)'
  for f in "${ips[@]}"
  do
     if [[ $f =~ $regex2 ]]
     then
      echo ${BASH_REMATCH[1]} ${BASH_REMATCH[5]}
      pis[j++]=${BASH_REMATCH[1]}
     fi
  done
}

sendoverssh() {
   if (( $# != 2 ))
   then
      echo 'usage: sendoverssh 10.1.1.1 "echo lala > ~/lalalala"'
      exit 1
   fi
   sshpass -p "raspberry" ssh "$1" -o StrictHostKeyChecking=no -o UserKnownHostsFile=/dev/null -l pi "$2"  
}


  

cleanscan
echo ---pis---
getpis
echo ---------
if (( $# == 1 ))
  then
  echo "command: $1"
 for ip in "${pis[@]}"
 do
    echo $ip
    sendoverssh $ip $1
    echo "done" 
 done
fi
