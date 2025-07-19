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

    int t,w,x;
    int tc,yc;
    printf("\nenter number of frames");
    scanf("%d",&t);
    printf("\nenter window size");
    scanf("%d",&w);
    tc=t;
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(15486);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");


    char start[1] = {0};
    sendto(sockfd, start, sizeof(start), 0,(struct sockaddr*)&server_addr, len);
    int dn;  while(c<6)
    {


            if(l==t)
            {
                    break;
            }
           printf("\nclient receiving packets");

            if(tc<w)
            {
                    dn=tc;
              printf("\nthe tc is %d",tc);
            for(int j=1;j<=dn;j++)
             {

                     recvfrom(sockfd, &received, sizeof(int), 0,(struct sockaddr*)&server_addr, &len);
                     printf("\nreceived packet %d",received);
              }

           }

          else
           {
            for (int i = 0; i < w; i++)
             {
              recvfrom(sockfd, &received, sizeof(int), 0,(struct sockaddr*)&server_addr, &len);
             printf("\nreceived packet %d",received);
             }
            }
       printf("\nenter the packet number for positive acknowledgement\nenter 0 for negative acknowledgement\n");

       if(tc<w)  {
                dn=tc;
               for(int j=1;j<=dn;j++)
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
         }
     else
      {
       for (int i = 0; i < w; i++)
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

      }
    }
    close(sockfd);
    return 0;
}
