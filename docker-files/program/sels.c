#include<stdio.h>
#include<stdlib.h>
#include<sys/ioctl.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<string.h>
char buffer[10];
void itoa(int f,char fstr[])
 {
  fstr[0]=f;
  fstr[1]='\0';
 }  
void main()
 {
    int sockfd,a[10],i;
    char gstr[10],istr[10],nstr[10];
    struct sockaddr_in servaddr,cliaddr;
    socklen_t len;
    sockfd=socket(AF_INET,SOCK_DGRAM,0);
    servaddr.sin_family=AF_INET;
    servaddr.sin_addr.s_addr=INADDR_ANY;
    servaddr.sin_port=htons(5382);
    bind(sockfd,(struct sockaddr*)&servaddr,sizeof(servaddr));
    printf("\nwaiting for client");
    len=sizeof(cliaddr);
    recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&len);
    int base=0;
    int tf,ws;
    printf("\nenter the total number of frames");
    scanf("%d",&tf);
    printf("\nenter the window size");
    scanf("%d",&ws);

    int p=0,m,num,n;
    for(i=0;i<ws;i++)
     {
        printf("\nsending packet%d",i);
	itoa(i,istr);
        strcpy(buffer,istr);
        sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,len);
     }
    while(p<tf)
     {
	m=0;     
      for(i=0;i<ws;i++)
       {
         recvfrom(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,&len);
         num=atoi(buffer);
         if(num==-1)
          {
            printf("\n positive acknowledgement");
            p++;
          }
         else
          {
            a[m]=num;
            m++;
          } 
       }
      int g;
      for(i=0;i<m;i++)
       {
         printf("\nresending packet%d",a[i]);
	 g=a[i];
	 itoa(g,gstr);
         strcpy(buffer,gstr);
         sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,len);
       } 
      for(i=m;i<ws;i++) //to check this line
       {
         base++;
         n=base;
	 itoa(n,nstr);
	 strcpy(buffer,nstr);
         printf("\nsending packet%d",n);
         sendto(sockfd,buffer,sizeof(buffer),0,(struct sockaddr*)&cliaddr,len);
       }
     }
    printf("\nall packets send"); 
 }
