#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
void main()
{
    int sockfd,connfd;
    char msg[100];
    struct sockaddr_in servaddr;
    sockfd=socket(AF_INET,SOCK_STREAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(9302);
    bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    listen(sockfd,5);
    connfd=accept(sockfd,NULL,NULL);
    printf("\nenter the message  \n\n");
    printf("\n");
    scanf("%s",msg);
    send(connfd,&msg,sizeof(msg),0);
    close(sockfd);

}
