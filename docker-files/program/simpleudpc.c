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
    char buffer[1024];
    socklen_t len=sizeof(servaddr);
    memset(&servaddr,0,sizeof(servaddr));
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=inet_addr("127.0.0.1");
    printf("\nenter the starting message");
    scanf("%s",buffer);
    sendto(sockfd,buffer,strlen(buffer),0,(struct sockaddr*)&servaddr,sizeof(servaddr));
    recvfrom(sockfd,msg,sizeof(msg),0,(struct sockaddr*)&servaddr,&len);
    printf("\nthe message is %s",msg);
    }
