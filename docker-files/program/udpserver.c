#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>	 

int check(int a[],int m)
{
	int flag=0;
	for(int i=0;i<100;i++)
	{ 
		if(a[i]==m)
		{
			flag=1;

		}
	}
    return(flag);
}    


#define SERVER_PORT 33151
#define BUFFER_SIZE 1024

int main() 
{
    int sockfd,i,t,ws,u=0,n=5;
    int m=0;
    int a[5];
    int ackr[100]={0};
    struct sockaddr_in server_addr, client_addr;
    socklen_t len;
    int buffer;
    
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   

   
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY; // Accept from any interface
    server_addr.sin_port = htons(SERVER_PORT);

   
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    printf("Server waiting for client...\n");

    // Wait for a message from client
    len = sizeof(client_addr);
    char temp_buffer[BUFFER_SIZE];
    recvfrom(sockfd, temp_buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr,&len);
    printf("\nenter total number of frames ");
    scanf("%d",&t);
    printf("\nenter the window size ");
    scanf("%d",&ws);
printf("\nenter any number to check");
scanf("%d",&buffer);
sendto(sockfd, &buffer, BUFFER_SIZE, 0, (struct sockaddr*)&client_addr,len);
  for (int i = 0; i < n; i++) {
        sendto(sockfd, &i, sizeof(int), 0,
               (struct sockaddr*)&client_addr, len);
        printf("Sent: %d\n", i);
        sleep(1);
  }
	close(sockfd);
	return 0;
}
