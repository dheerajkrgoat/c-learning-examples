// udp_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);
    int n,i;
    int w,t;
    printf("\nenter the number of frames");
    scanf("%d",&t);
    printf("\nenter the window size");
    scanf("%d",&w);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Wait for an initial message from client to get address
    char dummy[1];
    recvfrom(sockfd, dummy, sizeof(dummy), 0, (struct sockaddr*)&client_addr, &len);

    for ( i = 1; i < w; i++) {
        sendto(sockfd, &i, sizeof(int), 0,
               (struct sockaddr*)&client_addr, len);
        printf("Sent: %d\n", i);
        sleep(1); // delay to ensure client receives in time
    }
  for(i=1;i<=w;i++)
  { 
	  recvfrom(sockfd,&n,sizeof(int),0,(struct sockaddr*)&client_addr,&len);
	  printf("%d",n);
 }	  
    close(sockfd);
    return 0;
}
