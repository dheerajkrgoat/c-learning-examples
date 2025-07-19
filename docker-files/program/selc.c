#include<stdio.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<string.h>
#include<stdlib.h>
char buffer[10];
void itoa(int s,char sstr[])
 {
   sstr[0]=s;
   sstr[1]='\0';
 }
void main()
 {
    int sockfd,ack;
    char ackstr[10];
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(5382);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    strcpy(buffer,"start");
    sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
    int ws=4,n,i;
    len=sizeof(servaddr);
    while(1)
     {   
      for(i=0;i<ws;i++)
       {
         recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&servaddr,&len);
         n=atoi(buffer);
         printf("the packet%d recieved",n);
       }
      printf("\nenter 0 for positive acknowledgement");
      printf("\nenter the packet to be resent"); 
      for(i=0;i<ws;i++)
       {
        scanf("%d",&ack);
        itoa(ack,ackstr);
        strcpy(buffer,ackstr);
        sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
       } 
     }
   } 
