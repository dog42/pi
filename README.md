# pi

[ZIP](https://github.com/D0gi/pi/archive/master.zip)



#edit raspian.img

- make mountdir `sudo mkdir /media/$USER/bla`
- open img file whit `sudo kpartx -a <raspian.img>`
- mount `sudo mount /dev/mapper/loop0p2 /media/$USER/bla `
- go to mountdir `cd /media/$USER/bla`
- edit content as root and save 
- go out of mountdir `cd`
- `sync`
- umount `sudo umount /media/$USER/bla `
- close img file whit `sudo kpartx -d <raspian.img>`
- `sync`
- rm mountdir `sudo rm -r /media/$USER/bla`