#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
void main()
{
    int sockfd,connfd;
    int m;
    char msg[100];
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len=sizeof(servaddr);
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_port=htons(12435);
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_family=AF_INET;
    connect(sockfd,(struct sockaddr*)&servaddr,len);
    read(sockfd,&m,sizeof(int));
    printf("\n%d",m);
    printf("\nenter the message to server\n");
    scanf("%s",msg);
    write(sockfd,msg,sizeof(msg));
    printf("\n\nthe message has been sent");
    read(sockfd,msg,sizeof(msg));
    printf("\n\nthe message is %s",msg);
    read(sockfd,msg,sizeof(msg));
    printf("\n\nthe time from server is %s",msg);
}
