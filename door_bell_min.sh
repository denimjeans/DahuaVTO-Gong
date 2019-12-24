#/bin/bash
# this is door_bell_min.sh
# minimum required file
# change with chmod +x 
# change jpg:jpg with your USERNAME:PASSWORD
# change IP_OF_VTO to your IP address


PATH="/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/root"
export PATH

CURTIME=`date +"%d.%m.%y %H:%M"`
RINGING="/tmp/door_ringing"
DOOR="door"
 
proc()
{
  curl --user "jpg:jpg" --digest http://IP_OF_VTO/cgi-bin/snapshot.cgi -s -o /tmp/door.jpg
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
