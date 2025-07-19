#include<stdio.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<string.h>
void main()
{
    int n;
    char array[]="eth0";
    struct ifreq ifr;
    char *mac;
    ifr.ifr_addr.sa_family=AF_INET;
    n=socket(AF_INET,SOCK_DGRAM,0);
    strncpy(ifr.ifr_name,array,IFNAMSIZ-1);
    ioctl(n,SIOCGIFADDR,&ifr);
    mac=(unsigned char*)ifr.ifr_hwaddr.sa_data;
    printf("\n the mac address is %2X.%2X.%2X.%2X.%2X.%2X",mac[0],mac[1],mac[2],mac[3],mac[4],mac[5]);
    close(n);
    printf("\nthe IP address is %s",inet_ntoa(((struct sockaddr_in*)&ifr.ifr_addr)->sin_addr));
}
