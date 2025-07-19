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
 ascii[0]=(char)(num+48);
 ascii[1]='\0';
}
int main()
{
 char *p;
 int listenfd,x,i,n,w_size,w_curr=0,w_end;
 struct sockaddr_in serv_addr;
 char sendBuff[80];
 int buffer[20],s;
 listenfd=socket(AF_INET,SOCK_DGRAM,0);
 memset(&serv_addr,'0',sizeof(serv_addr));
 memset(sendBuff,'0',sizeof(sendBuff));
 serv_addr.sin_family=AF_INET;
 serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
 serv_addr.sin_port=htons(2700);
 bind(listenfd,(struct sockaddr*)&serv_addr,sizeof(serv_addr));
 socklen_t len;
 len=sizeof(struct sockaddr_in);
 n=recvfrom(listenfd,sendBuff,sizeof(sendBuff),0,(struct sockaddr*)&serv_addr,&len);
 sendBuff[n]=0;
 w_size=atoi(sendBuff);
 printf("Packets to be sent : ");
 for(i=0;i<w_size;i++)
 scanf("%d",&buffer[i]);
 printf("No. of frames to be sent at once : ");
 scanf("%d",&s);
 w_end=s;
 while(w_size>w_curr)
 {
  while( w_curr<w_end)
  {
   printf("\n");
   itoa(buffer[w_curr],sendBuff);
   printf("Packet %d sent to client",buffer[w_curr]);
   n=sendto(listenfd,sendBuff,strlen(sendBuff),0,(struct sockaddr*)&serv_addr,len);
   strcpy(sendBuff," ");
   w_curr++;
  }
  strcpy(sendBuff,"END");
  sendto(listenfd,sendBuff,strlen(sendBuff),0,(struct sockaddr *)&serv_addr,len);
  strcpy(sendBuff," ");
  n=recvfrom(listenfd,sendBuff,sizeof(sendBuff),0,(struct sockaddr *)&serv_addr,&len);
  sendBuff[n]=0;
  if(sendBuff[0]=='N')
  {
   printf("\nReceived negative acknowledemet for packet %c from client\n",sendBuff[1]);
   p=sendBuff;
   p++;
   for(i=0;i<w_size;i++)
   {
    if(buffer[i]==atoi(p))
    w_curr=i;
   }
   w_end=w_curr+s;
  }
  else
  {
   printf("\nReceived positive acknowledgement for packet %c from client\n",sendBuff[1]);
   w_end+=s;
  }
  if(w_end>w_size)
  w_end=w_size;
 }
 return 0;
}
