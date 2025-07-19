#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
//all the ideas of connection of the server and client is as same as all other programs.
//the key idea of this program is sending the packets as numbers and receives the acknowledgements also as numbers,this will reduce the complexity of conversions done,0 is used to denote negative acknowledgement and packet number will be send to positively aclnowledge the packet.the positively acknowledged packet numbers is stored in a array and this array is checked each time before sendind the packets.the packets that are not being in the array will be sent in next iteration,this will reduce the complexity of the problem,hope you all will understand this program

int check(int ar[],int o)
{
        int flag=0;
        for(int i=0;i<100;i++)
        {
                if(ar[i]==o)
                {
                        flag=1;
                }
        }
        return(flag);
}
//differ from the given program I have used integer variable to send and receive data
int main()
{
    int sockfd,g;
    int a[100]={0};//array storing the acknowledged packets,initially contain value 0
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);

 
    int x;
    int tc,yc;
    int m=-1;//I have used this as array indexing variable
    int received;//to receive the acknowledgement number
    int c=0;//to control the while loop,the while(TRUE) will not always works.
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12856);
    server_addr.sin_addr.s_addr = INADDR_ANY;
  
 
    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    
    char start[1];//starting message asertain connection
    recvfrom(sockfd, start, sizeof(start), 0,
             (struct sockaddr*)&client_addr, &len);
    int w,t;//the variables for total number of frames and window size
    printf("\nenter the number of frames ");
    scanf("%d",&t);
    tc=t;
    printf("\nenter the window size ");
    scanf("%d",&w);
int y;//this is for checking the number of packets sent in one iteration
int l=0;//It will be incremented by 1 after receiving positive acknowledgement,if the value of l become total number of packets,it implies all packets are acknowledged,I have used it to check in the initial phase of next while loop
   
    while(c<6)
    {
            
            ND:
            y=0;
            if(l==t)
            {
                    break;
            }
	    if(tc<w)
	    {
		    yc=0;
		    for(int i=1;i<t;i++)
		    {
			     g=check(a,i);//refer the function definition,search for the passed value in passed array

                             if(g==0)
                              {
                               yc++;
                               sendto(sockfd, &i, sizeof(int), 0,(struct sockaddr*)&client_addr, len);
                               printf("Sent: %d\n", i);
                               sleep(1);
			       if(yc==tc)
			       {
				    break;
			       }
			      } 
		    }
		    goto DN;
	    }
    printf("\nserver sending packets\n");

    for (int i = 1; i <=t; i++)//it will check all the packets
    {
            if(y==w)//y will be incremented after sending a packet andif the value of y become w,it implies a window has been sent
            {
                    break;
            } 
	    g=check(a,i);//refer the function definition,search for the passed value in passed array

            if(g==0)
            {
                    y++;
        sendto(sockfd, &i, sizeof(int), 0,(struct sockaddr*)&client_addr, len);
        printf("Sent: %d\n", i);
        sleep(1);//I refered this function from chatGPT,it is used to ensure a delay so that the client can receive concurrently
            }
    }
   DN:
   if(tc<w)
   {
	    for (int i = 0; i < tc; i++)
    {
        recvfrom(sockfd, &received, sizeof(int), 0, (struct sockaddr*)&client_addr, &len);
        if(received==0)//refer client side code
        {
        printf("\nReceived negative acknowledgement\n");
        }
        else
        {
                a[++m]=received;//stored in the above mentioned array,the array contains the acknowledged packets

                l++;
                tc--;
                printf("\npositive acknowledgement for packet %d",received);
	}
    
    }
	    goto ND;
   }
   printf("\nreceiving acknowledgement\n");
    for (int i = 0; i < w; i++)
    {
        recvfrom(sockfd, &received, sizeof(int), 0, (struct sockaddr*)&client_addr, &len);
        if(received==0)//refer client side code
        {
        printf("\nReceived negative acknowledgement\n");
        }
        else
        {
                a[++m]=received;//stored in the above mentioned array,the array contains the acknowledged packets

                l++;
		tc--;
                printf("\npositive acknowledgement for packet %d",received);
                //incrementing array indexing variable
        }
 
    }
  }
    
    close(sockfd);
    return 0;
                             
} 
