#include <stdio.h>
#include <strings.h>
#include <sys/types.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include<netinet/in.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{

char fromserver[100];
char message1[] =" Hello Beena " ;
int sockfd, n;
struct sockaddr_in servaddr;
servaddr.sin_addr.s_addr =INADDR_ANY;
servaddr.sin_port = htons(5000);
servaddr.sin_family = AF_INET;
// create datagram socket
sockfd = socket(AF_INET, SOCK_DGRAM, 0);
// connect to server
if(connect(sockfd, (struct sockaddr *)&servaddr,

sizeof(servaddr)) < 0)

{

printf("\n Error : Connect Failed \n");
exit(0);

}
// request to send datagram
// no need to specify server address in sendto
// connect stores the peers IP and port
sendto(sockfd, message1,sizeof(message1), 0, (struct

sockaddr*)NULL, 0);

// waiting for response
recvfrom(sockfd, fromserver, sizeof(fromserver), 0, (struct

sockaddr*)NULL, 0);
puts(fromserver);
// close the descriptor
close(sockfd);
}
