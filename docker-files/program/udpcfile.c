#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
void main()
{
	int sockfd;
	char buffer[100];
	struct sockaddr_in servaddr,cliaddr;
        char *filename="sample.txt";
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(42156);
	FILE *fp=fopen(filename,"r");
	while((fgets(buffer,100,fp))!=NULL)
	{
		printf("\nsending %s",buffer);
		sendto(sockfd,buffer,100,0,(struct sockaddr*)&servaddr,sizeof(servaddr));
	}
	strcpy(buffer,"END");
	sendto(sockfd,buffer,100,0,(struct sockaddr*)&servaddr,sizeof(servaddr));
	fclose(fp);
        close(sockfd);
}
