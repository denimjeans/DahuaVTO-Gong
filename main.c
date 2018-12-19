/* Receiver/client multicast Datagram example. */
/*
 * based on Antony Courtney's listener
 * Modified by: Frédéric Bastien (25/03/04)
 * and now modified by Oktay Oeztueter (12/19/2018), maybe not the best style of programming, but works :)
 * to compile without warning and work correctly
 */
 
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h> // for open
#include <unistd.h> // for close
 
#define SCRIPT "/root/bin/door_bell.sh"
#define VERSION "0.3"

struct sockaddr_in localSock;
struct ip_mreq group;
int sd;
int datalen;
char databuf[1500];
int debug=0;

static inline void printc( const char* ptr, int n)
{
    int i=0,l=0;
    
    for(; i<n; i+=16)
    {
        for(l=0; l<16; ++l)
        {
            if((l+i)<n)
                printf(" %.2x",(unsigned char)ptr[l+i]);
        }
        if (n>16)
            printf("\n\t ");
    }
    printf("\n");
}

int main(int argc, char *argv[])
{


if(argc>=4){
	debug=1;
	printf("Debug is ON\r\n");
}
if(argc<2)
{
	printf("%s %s\r\nusage:%s localIP [script default /root/bin/door_bell.sh] [debug]\r\n",argv[0],VERSION,argv[0]);
	exit(0);
}


printf("Local IP: %s\r\nScript: %s\r\n",argv[1],argc>2?argv[2]:SCRIPT);
printf("sending test images, might take few seconds...\r\n");
unsigned int s=system(SCRIPT);
if(s>0){
	printf("Something went wrong with the userscript %s, please check if existing and executable [System:%d]\r\n",SCRIPT,s);
exit(0);
}
	//printf ("argc: %d\r\n",argc);
/* Create a datagram socket on which to receive. */
sd = socket(AF_INET, SOCK_DGRAM, 0);
if(sd < 0)
{
perror("Opening datagram socket error");
exit(1);
}
else
printf("Opening datagram socket....OK.\n");
 
/* Enable SO_REUSEADDR to allow multiple instances of this */
/* application to receive copies of the multicast datagrams. */
{
int reuse = 1;
if(setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse, sizeof(reuse)) < 0)
{
perror("Setting SO_REUSEADDR error");
close(sd);
exit(1);
}
else
printf("Setting SO_REUSEADDR...OK.\n");
}
 
/* Bind to the proper port number with the IP address */
/* specified as INADDR_ANY. */
memset((char *) &localSock, 0, sizeof(localSock));
localSock.sin_family = AF_INET;
localSock.sin_port = htons(30000);
localSock.sin_addr.s_addr = INADDR_ANY;
if(bind(sd, (struct sockaddr*)&localSock, sizeof(localSock)))
{
perror("Binding datagram socket error");
close(sd);
exit(1);
}
else
printf("Binding datagram socket...OK.\n");
 
/* Join the multicast group 226.1.1.1 on the local 203.106.93.94 */
/* interface. Note that this IP_ADD_MEMBERSHIP option must be */
/* called for each local interface over which the multicast */
/* datagrams are to be received. */
group.imr_multiaddr.s_addr = inet_addr("224.0.2.13");
group.imr_interface.s_addr = inet_addr(argv[1]);
if(setsockopt(sd, IPPROTO_IP, IP_ADD_MEMBERSHIP, (char *)&group, sizeof(group)) < 0)
{
perror("Adding multicast group error");
close(sd);
exit(1);
}
else
printf("Adding multicast group...OK.\n");
 
/* Read from the socket. */
int ru=0;
datalen = sizeof(databuf);

while (1)
{
	ru=read(sd, databuf, datalen) ;
	if(ru < 0)
	{
		perror("Reading datagram message error");
		close(sd);
		exit(1);
	}
	else
	{
		

		if(debug==1)
		{
			printf("The size of message from multicast server is: %d bytes\r\n", ru);
			printc(databuf, ru);
		}
		else if (ru==16){
			//printf("Reading datagram message...OK.\n");
			printf("The size of message from multicast server is: %d bytes\r\n", ru);
			printc(databuf, ru);
			system(SCRIPT);
		}
		
		
	}
}
return 0;
}
 
