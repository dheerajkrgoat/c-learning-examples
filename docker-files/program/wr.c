// udp_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int check(int ar[],int o)
{
	int flag=0;
	for(int i=0;i<100;i++)
	{	
		if(ar[i]==o)
		{
			flag=1;
		}
	}
	return(flag);
}
int main() 
{
    int sockfd,g;
    int a[100]={0};
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);
    
 
    int m=0;
    int received;
    int c=0;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Server setup
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(65421);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    // Bind
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Wait for initial message to get client address
    char dummy[1];
    recvfrom(sockfd, dummy, sizeof(dummy), 0,
             (struct sockaddr*)&client_addr, &len);
    int w,t;
    printf("\nenter the number of frames ");
    scanf("%d",&t);
    printf("\nenter the window size ");
    scanf("%d",&w);
int y;
int l=0;
    // Send 5 numbers
    while(c<6)
    {
	    y=0;
	    if(l==t)
	    {
		    break;
	    }
    printf("Server sending:\n");

    for (int i = 1; i <=t; i++) 
    {
	    if(y==w)
	    {
		    break;
	    }
	    g=check(a,i);
	
	    if(g==0)
	    {
		    y++;
        sendto(sockfd, &i, sizeof(int), 0,
               (struct sockaddr*)&client_addr, len);
        printf("Sent: %d\n", i);
        sleep(1); 
	    }// Optional pacing
    }

    // Receive 5 numbers back
    printf("\nServer receiving from client:\n");
    for (int i = 0; i < w; i++) 
    {
        recvfrom(sockfd, &received, sizeof(int), 0,
                 (struct sockaddr*)&client_addr, &len);
	if(received==0)
	{
        printf("\nReceived negative acknowledgement\n");
	}
	else
	{
		a[m]=received;
	
		l++;
		printf("\npositive acknowledgement for packet %d",received);
		m++;
        }
    }
    }
    close(sockfd);
    return 0;
}
