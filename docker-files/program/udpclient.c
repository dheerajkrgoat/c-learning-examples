#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

/*void itoa(int r,char rstr[])
 {
         int i=0;
         if(r==0)
         {
                 rstr[i++]='0';
                 rstr[i]='\0';
         }
         while(r>0)
         {
                 rstr[i++]=(r%10)+'0';
                 r=r/10;
         }
         rstr[i]='\0';
         for(int j=0,k=i-i;j<k;j++,k++)
         {
                 char temp=rstr[j];
                 rstr[j]=rstr[k];
                 rstr[k]=temp;
         }
 }*/	 
#define SERVER_PORT 33151
#define BUFFER_SIZE 1024

int main() {
    int sockfd,ack,n=5;
    int number;
    char ackstr[5];
    struct sockaddr_in server_addr;
    socklen_t len;
    int buffer;

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    // Server address settings
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(SERVER_PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // localhost

    // Send dummy message to server
    char hello[1024];
    printf("\nenter the starting message\n");
    scanf("%s",hello);
    sendto(sockfd, hello, strlen(hello), 0, (struct sockaddr*)&server_addr, sizeof(server_addr));
int i;
    // Receive message from server
    len = sizeof(server_addr);
    recvfrom(sockfd, &buffer, BUFFER_SIZE, 0, (struct sockaddr*)&server_addr, &len);
    printf("the checking number is %d",buffer);

    for (int i = 0; i < n; i++) {
        recvfrom(sockfd, &number, sizeof(int), 0,
                 (struct sockaddr*)&server_addr, &len);
        printf("Received: %d\n", number);
    }
    close(sockfd);
    return 0;
}
    
