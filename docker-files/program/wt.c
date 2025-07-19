// udp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);
    int received[5];
    int to_send;
    int c=0;
    int l=0;

    // Create socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Server setup

    int t,w;
    printf("\nenter number of frames");
    scanf("%d",&t);
    printf("\nenter window size");
    scanf("%d",&w);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(65421);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send initial dummy message to notify server
    char dummy[1] = {0};
    sendto(sockfd, dummy, sizeof(dummy), 0,
           (struct sockaddr*)&server_addr, len);

    // Receive 5 numbers
    while(c<6)
    {
	    if(l==t)
	    {
		    break;
	    }
    printf("Client received from server:\n");
    for (int i = 0; i < w; i++) {
        recvfrom(sockfd, &received[i], sizeof(int), 0,
                 (struct sockaddr*)&server_addr, &len);
        printf("Number %d: %d\n", i + 1, received[i]);
    }

    // Let user send any 5 numbers (including 0)
    printf("\nEnter 5 numbers to send back to server (can include 0 or any value):\n");
    for (int i = 0; i < w; i++) 
    {
        printf("\nenter the packet number for positive acknowledgement\nenter 0 for negative acknowledgement");

        scanf("%d", &to_send);
        if(to_send!=0)
	{
		l++;
	}	
        sendto(sockfd, &to_send, sizeof(int), 0,
               (struct sockaddr*)&server_addr, len);
    }
     c++;
    }

    close(sockfd);
    return 0;
}
