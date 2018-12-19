# DahuaVTO-Gong
A small utiliy or workaround to get the VTO ring information and the perform a script with the desired commands.

compile with 
main.c -o mcl
the script must exists before
then start with: mcl 192.168.1.10 /path_to_your/script
or with screen: screen  -S "dahua"  -d -m /root/bin/mcl 192.168.200.77 
this listens and perform the script ones someone rings.
if you find a better way to snif the ring, let me know :)


mcl is the precompiled version for the raspberry pi 3, olders might also work.  if not, compiling is not so difficuilt.
