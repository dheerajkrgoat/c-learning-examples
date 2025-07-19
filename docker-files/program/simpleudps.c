#include<stdio.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<string.h>
#include<stdlib.h>
#include<netinet/in.h>
void main()
 {
    int sockfd;
    struct sockaddr_in servaddr,cliaddr;
    char msg[100];
    memset(&servaddr,0,sizeof(servaddr));
    memset(&cliaddr,0,sizeof(cliaddr));
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(5918);
    int b=bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    if(b<0)
     {
        printf("\nbinding not possible");
     }
    printf("\nenter the message");
    scanf("%s",msg);
    printf("\nthe message is %s",msg);
    sendto(sockfd,msg,strlen(msg),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr));
 }
