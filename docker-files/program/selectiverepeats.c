// Selective Repeat Protocol Simulation using UDP // Server Side - Resends only NAK'd frames, slides window on ACKs

#include <stdio.h> #include <stdlib.h> #include <string.h> #include <unistd.h> #include <arpa/inet.h>

#define PORT 5382 #define MAX 1024

char buffer[10];

int main() { int sockfd; struct sockaddr_in servaddr, cliaddr; socklen_t len = sizeof(cliaddr);

sockfd = socket(AF_INET, SOCK_DGRAM, 0);
servaddr.sin_family = AF_INET;
servaddr.sin_addr.s_addr = INADDR_ANY;
servaddr.sin_port = htons(PORT);

bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

printf("Waiting for client...\n");
recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len); // wait for "start"

int totalFrames, windowSize;
printf("Enter total number of frames to send: ");
scanf("%d", &totalFrames);
printf("Enter window size: ");
scanf("%d", &windowSize);

int sent = 1;
int acknowledged[100] = {0};

while (1) {
    // Send window
    for (int i = 0; i < windowSize && sent + i <= totalFrames; i++) {
        int frameNum = sent + i;
        if (!acknowledged[frameNum]) {
            sprintf(buffer, "%d", frameNum);
            sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, len);
            printf("Sent frame: %d\n", frameNum);
        }
    }

    // Receive ACKs
    for (int i = 0; i < windowSize && sent <= totalFrames; i++) {
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);
        int ack = atoi(buffer);
        if (ack == 0) {
            printf("ACK received for frame %d\n", sent);
            acknowledged[sent] = 1;
            sent++;
        } else {
            printf("NAK received for frame %d\n", ack);
            acknowledged[ack] = 0;  // explicitly mark for resend
        }
    }

    // Exit if all frames are acknowledged
    int allAcked = 1;
    for (int i = 1; i <= totalFrames; i++) {
        if (!acknowledged[i]) {
            allAcked = 0;
            break;
        }
    }
    if (allAcked) break;
}

printf("All frames sent and acknowledged!\n");
close(sockfd);
return 0;

}
