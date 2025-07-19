#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
void main()
{
    int sockfd;
    char msg[100];
    struct sockaddr_in servaddr,cliaddr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(9302);
    connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    recv(sockfd,&msg,sizeof(msg),0);
    printf("\nthe message from server %s\n",msg);
    close(sockfd);
}
