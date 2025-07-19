#include<stdio.h>
#include<arpa/inet.h>
#include<string.h>
#include<stdlib.h>
#include<sys/socket.h>
#include<unistd.h>
#include<time.h>
void main()
{
        int sockfd,connfd;
        char msg[100],buffer[100];
        struct sockaddr_in servaddr,cliaddr;
        sockfd=socket(AF_INET,SOCK_STREAM,0);
        servaddr.sin_family=AF_INET;
        servaddr.sin_addr.s_addr=INADDR_ANY;
        servaddr.sin_port=htons(12675);
	connect(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	strcpy(msg,"hello");
	for(int i=0;i<3;i++)
	{
	send(sockfd,msg,sizeof(msg),0);
	printf("\nthe message sent");
	}
	recv(sockfd,buffer,sizeof(buffer),0);
	printf("\nthe message has been echoed-back %s",buffer);
	for(int i=0;i<4;i++)
	{
	recv(sockfd,buffer,sizeof(buffer),0);
	printf("\nthe message is %s",buffer);
	}
	close(sockfd);
}
