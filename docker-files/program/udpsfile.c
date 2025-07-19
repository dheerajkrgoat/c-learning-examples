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
	socklen_t len=sizeof(cliaddr);
	sockfd=socket(AF_INET,SOCK_DGRAM,0);
	servaddr.sin_family=AF_INET;
	servaddr.sin_addr.s_addr=INADDR_ANY;
	servaddr.sin_port=htons(42156);
	char *filename="serv.txt";
	bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
	FILE *fp=fopen(filename,"w");
	int c=0;
	while(c<6)
        {
		recvfrom(sockfd,buffer,100,0,(struct sockaddr*)&cliaddr,&len);
		if(strcmp(buffer,"END")==0)
			 {
				 break;
			 }
		else
		{
			printf("\nreceiving %s",buffer);
			fprintf(fp,"%s",buffer);
			bzero(buffer,100);
		}
		fclose(fp);
		printf("\ndata transfer complete");
		close(sockfd);
	}
}
