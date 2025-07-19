#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() 
{
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);
    int received;
    int n;
    int c=0;
    int l=0;

  
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    int t,w;
    int tc,yc;
    printf("\nenter number of frames");
    scanf("%d",&t);
    printf("\nenter window size");
    scanf("%d",&w);
    tc=t;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12856);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    
    char start[1] = {0};
    sendto(sockfd, start, sizeof(start), 0,(struct sockaddr*)&server_addr, len);
    while(c<6)
    {
	    
	    ND:
            if(l==t)
            {
                    break;
            }
    printf("\nclient receiving packets");
    if(tc<w)
    { 
	    for(int i=0;i<tc;i++)
	    {
		     recvfrom(sockfd, &received, sizeof(int), 0,(struct sockaddr*)&server_addr, &len);
                     printf("\nreceived packet %d",received);
	    }
    
	    goto DN;
    }
    for (int i = 0; i < w; i++) 
    {
        recvfrom(sockfd, &received, sizeof(int), 0,(struct sockaddr*)&server_addr, &len);
        printf("\nreceived packet %d",received);
    }

       DN:
       printf("\nenter the packet number for positive acknowledgement\nenter 0 for negative acknowledgement");
       if(tc<w)
       {
	       for(int i=0;i<tc;i++)
	       {
                scanf("%d", &n);
               if(n!=0)
               {
                printf("\nsent positive acknowledgement for packet %d\n",n);
                l++;
		tc--;
	       }
	         else
        {
                printf("\nsent negative acknowledgement\n");
        }
        sendto(sockfd, &n, sizeof(int), 0,(struct sockaddr*)&server_addr, len);
	       }
	       goto ND;
	}

    for (int i = 0; i < w; i++)
    {
       

        scanf("%d", &n);
        if(n!=0)
        {
		printf("\nsent positive acknowledgement for packet %d\n",n);
                l++;
		tc--;
		/*if(l==t)
		{
			goto DN;
		}*/
        }
	else
	{
		printf("\nsent negative acknowledgement\n");
	}
        sendto(sockfd, &n, sizeof(int), 0,(struct sockaddr*)&server_addr, len);
    }
    
  }
    //DN:
    close(sockfd);
    return 0;
}
                          
