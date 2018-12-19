# DahuaVTO-Gong
A small utiliy or workaround to get the VTO ring information.

compile with 
main.c -o mcl
the script must exists before
then start with: mcl 192.168.1.10 /path_to_your/script
or with screen: screen  -S "dahua"  -d -m /root/bin/mcl 192.168.200.77 
this listens and perform the script ones someone rings.
if you find a better way to snif the ring, let me know :)
