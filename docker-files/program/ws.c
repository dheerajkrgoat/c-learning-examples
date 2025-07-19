// udp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);
    int i,n,w,t;
    int number;
    printf("\nenter the number of frames");
    scanf("%d",&t);
    printf("\nenter the window size");
    scanf("%d",&w);
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send dummy message to tell server our address
    char dummy[1] = {0};
    sendto(sockfd, dummy, sizeof(dummy), 0,
           (struct sockaddr*)&server_addr,len);

    for ( i = 0; i < w; i++)
    {
        recvfrom(sockfd, &number, sizeof(int), 0,
                 (struct sockaddr*)&server_addr,&len);
        printf("Received: %d\n", number);
    }
    printf("\nenter 0 for negative acknowledgement\nenter packet number for positive acknowledgement");
    for(i=1;i<=w;i++)
    {
	    scanf("%d",&n);
	    sendto(sockfd,&n,sizeof(int),0,(struct sockaddr*)&server_addr,len);
	    printf("\n sent %d\n",n);
    }

    close(sockfd);
    return 0;
}
