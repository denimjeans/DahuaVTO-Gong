#/bin/bash
# this is door_bell.sh
# change with chmod +x 
# this script plays a sound, send message via telegram-cli, saves 4 pix in archive, and display via feh the image. 
# for testing you might only use sound or echo something

PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/root"
export PATH

CURTIME=`date +"%d.%m.%y %H:%M"`
RINGING="/tmp/door_ringing"
DOOR="door"
TELEGRAM="/root/bin/telegram-cli"
TELEGRAM_CERT="/etc/telegram-cli/server.pub"


noti(){
/usr/bin/aplay /mnt/okt_ring2.wav &
}

proc()
{
    noti &
    $TELEGRAM -k $TELEGRAM_CERT -u root -W -D -e "msg user#YOURUSER $CURTIME: Es klingelt"
        curl --user "view:only" --digest http://door/cgi-bin/snapshot.cgi -s -o /tmp/door1.jpg
    sleep 0.1
         #feh -D 60 /tmp/door1.jpg --cycle-once -g 480x288+0+100 &

        $TELEGRAM -k $TELEGRAM_CERT -u root -W -D -e "send_photo user#YOURUSER /tmp/door1.jpg"

         feh -D 60 /tmp/door1.jpg --cycle-once -g 480x288+0+100 &
sleep 0.1
        curl --user "jpg:jpg" --digest http://door/cgi-bin/snapshot.cgi -s -o /tmp/door2.jpg
#        feh -D 55 /tmp/door2.jpg --cycle-once -g 480x288+0+400 &
        sleep 0.5
        $TELEGRAM -k $TELEGRAM_CERT -u root -W -D -e "send_photo user#105477772 /tmp/door2.jpg"

    curl --user "jpg:jpg" --digest http://door/cgi-bin/snapshot.cgi -s -o /tmp/door3.jpg
    sleep 0.1
    curl --user "jpg:jpg" --digest http://door/cgi-bin/snapshot.cgi -s -o /tmp/door4.jpg

    dt="`date +%d.%m.%Y_%H-%M`.jpg"
    cp /tmp/door1.jpg /media/NTFS8/door/door1_$dt
    cp /tmp/door2.jpg /media/NTFS8/door/door2_$dt
    cp /tmp/door3.jpg /media/NTFS8/door/door3_$dt
    cp /tmp/door4.jpg /media/NTFS8/door/door4_$dt

feh -D 55 /tmp/door2.jpg --cycle-once -g 480x288+0+400 &
}


if [ -e $RINGING ]; then
        if [ $(( (`date +%s` - `stat $RINGING -c%Z` ) / 60 )) != 0 ]; then
                touch $RINGING
                proc
        fi
else
        touch $RINGING
        proc
fi


exit

