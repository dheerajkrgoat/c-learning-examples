#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<errno.h>
#include<string.h>
#include<sys/types.h>
void itoa(int num,char ascii[])
{
 if(num<=9)
 {
  ascii[0]=(char)(num+48);
  ascii[1]='\0';
 }
 else
 {
  ascii[0]=(char)(num/10+48);
  ascii[1]=(char)(num%10+48);
  ascii[2]='\0';
 }
}
int main(void)
{
 FILE *fp;
 int sockfd=0,n,x,i,w_size,w_curr1=0,y=0;
 char recvBuff[80],ack[20],response[20],ch,*p;
 int buffer[20];
 struct sockaddr_in serv_addr;
 socklen_t len;
 memset(recvBuff,'0',sizeof(recvBuff));
 sockfd=socket(AF_INET,SOCK_DGRAM,0);
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_port=htons(2700);
 serv_addr.sin_addr.s_addr=inet_addr("0.0.0.0");
 len=sizeof(serv_addr);
 printf("Requesting for connection\n");
 printf("Window size : ");
 scanf("%d",&w_size);
 itoa(w_size,recvBuff);
 sendto(sockfd,recvBuff,strlen(recvBuff),0,(struct
 sockaddr*)&serv_addr,len);
 printf("Enter the packets to be received from server: ");
 for(i=0;i<w_size;i++)
 scanf("%d",&buffer[i]);
 while(w_curr1<w_size)
 {
  y=1;
  while(y)
  {
   n=recvfrom(sockfd,recvBuff,sizeof(recvBuff),0,(struct sockaddr*)&serv_addr,&len);
   recvBuff[n]='\0'; 
   if((strcmp(recvBuff,"END"))==0)
   y=0;
   else
   {
    printf("Received packet %s from server\n",recvBuff);
    w_curr1++;
   }
   strcpy(recvBuff," ");
  }
  printf("Enter the acknowlwdgement - A-ack/N-neg ack along with seq number : ");
  scanf("%s",recvBuff);
  sendto(sockfd,recvBuff,strlen(recvBuff),0,(struct sockaddr*)&serv_addr,len);
  if(recvBuff[0]=='N')
  {
   p=recvBuff;
   p++;
   for(i=0;i<w_size;i++)
   if(buffer[i]==atoi(p))
   w_curr1=i;
  }
 }
 return 0;
}
