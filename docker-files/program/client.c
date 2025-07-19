// #pragma comment(lib, "Ws2_32.lib")
#include <stdio.h>
#include <stdlib.h>
#include<netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
// #include <WinSock2.h>
// #include <WS2tcpip.h>
int main()
{
int sockfd, connfd;
struct sockaddr_in servaddr, cli;
char msg[80];
sockfd = socket(AF_INET, SOCK_STREAM, 0);
if (sockfd == -1) {
printf("socket creation failed...\n");
exit(0);
}
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(9302);
connect(sockfd, (struct sockaddr
*)&servaddr,sizeof(servaddr));
recv(sockfd, &msg, sizeof(msg),0);
printf("Data from the server is %s",msg);
}
