#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <time.h>
void main()
{
    int sockfd,connfd;
    int msg;
    socklen_t len;
    struct sockaddr_in servaddr,cliaddr;
    len=sizeof(cliaddr);
    char m[100];
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_port=htons(12435);
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_family=AF_INET;
    bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(sockfd,5);
    connfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
    printf("\n enter the message\n");
    scanf("%d",&msg);
    write(connfd,&msg,sizeof(int));
    read(connfd,m,sizeof(m));
    printf("\n\nthe message from client is %s",m);
    write(connfd,m,sizeof(m));
    printf("\n\nthe message has been echoed back");
    time_t now=time(NULL);
    snprintf(m,sizeof(m),"%s",ctime(&now));
    printf("\n\nthe time is %s",m);
    write(connfd,m,sizeof(m));
}
