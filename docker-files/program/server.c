// #pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <sys/socket.h>
// #include <WinSock2.h>
// #include <WS2tcpip.h>
#include <sys/types.h>
#include<unistd.h>
int main()
{
int sockfd, connfd, len;
struct sockaddr_in servaddr, clientaddr;
char msg[80];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(9302);
bind(sockfd, (struct sockaddr*)&servaddr,sizeof(servaddr) );
listen(sockfd, 5);
connfd = accept(sockfd,NULL,NULL);
printf("Enter message\n");
scanf("%s",msg);
send(connfd,&msg,sizeof(msg),0);
close(sockfd);
}
