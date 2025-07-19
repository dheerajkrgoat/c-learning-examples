#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<netinet/in.h>
#include<sys/types.h>
#include<sys/socket.h>
void main()
{
    int so;
    char buffer[100];
    char *m="hello server";
    struct sockaddr_in s,c;
    so=socket(AF_INET,SOCK_DGRAM,0);
   // socklen_t=len;
    s.sin_family=AF_INET;
    s.sin_addr.s_addr=inet_addr("127.0.0.1");
    s.sin_port=htons(5533);
    //len=sizeof(s);
    connect(so,(struct sockaddr*)&s,sizeof(s));
    sendto(so,m,strlen(m),0,(struct sockaddr*)NULL,0);
    recvfrom(so,buffer,sizeof(buffer),0,(struct sockaddr*)NULL,0);
    printf("\n the message is %s",buffer);
}
