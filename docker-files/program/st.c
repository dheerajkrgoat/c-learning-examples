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
	time_t now=time(NULL);
	sockfd=socket(AF_INET,SOCK_STREAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(12675);
	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	listen(sockfd,5);
	socklen_t len=sizeof(cliaddr);
	connfd=accept(sockfd,(struct sockaddr*)&cliaddr,&len);
	for(int i=0;i<3;i++)
	{
	recv(connfd,msg,sizeof(msg),0);
	printf("\nthe received message is %s",msg);
	}
	strcpy(buffer,msg);
	send(connfd,buffer,sizeof(buffer),0);
	printf("\nthe message has been echoed-back");
	snprintf(buffer,sizeof(buffer),"%s",ctime(&now));
	printf("\nthe time is %s",buffer);
	for(int i=0;i<4;i++)
	{
		scanf("%s",msg);
		strcpy(buffer,msg);
	write(connfd,buffer,sizeof(buffer));
	}
	close(sockfd);
}

