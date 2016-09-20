# pi

[ZIP](https://github.com/D0gi/pi/archive/master.zip)



#edit raspian.img

-make mountdir `mkdir /media/<username>/bla`
-open img file whit `sudo kpartx -a raspian.img`
-mount `sudo mount /dev/mapper/loop0p2 /media/<username>/bla `
-go to mountdir `cd /media/<username>/bla`
-edit content as root and save 
-`sync`
-umount `sudo umount /media/<username>/bla `
-close img file whit `sudo kpartx -a raspian.img`
-`sync`
-rm mountdir `rm /media/<username>/bla`
