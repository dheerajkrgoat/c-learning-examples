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
    int sockfd;
    char buffer[100];
    char *msg="hello Dheeraj";
    struct sockaddr_in s,c;
    socklen_t len;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    if(sockfd<0)
     {
      printf("binding failed");
     }
    s.sin_family=AF_INET;
    s.sin_addr.s_addr=INADDR_ANY;
    s.sin_port=htons(5533);
    bzero(&s,sizeof(s));
    int t=bind(sockfd,(struct sockaddr*)&s,sizeof(s));
    if(t<0)
     {
      printf("binding failed");
     } 
    len=sizeof(c);
    printf("\n waiting for client");
    int n=recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&c,&len);
    buffer[n]='\n';
    printf("\nthe message is:%s",buffer);
    sendto(sockfd,msg,strlen(msg),0,(struct sockaddr*)&c,len);
    close(sockfd);
}
