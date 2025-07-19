#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1234
#define BUFFER_SIZE 1024

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);
    char buffer[BUFFER_SIZE];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Send start message
    strcpy(buffer, "start");
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&servaddr, len);

    while (1) {
        printf("\nWaiting for frames from server...\n");

        // Receive up to 4 frames
        int frames[4];
        for (int i = 0; i < 4; i++) {
            int recv_len = recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&servaddr, &len);
            if (recv_len <= 0) break;

            frames[i] = atoi(buffer);
            if (frames[i] == 0) break;
            printf("Received frame: %d\n", frames[i]);
        }

        printf("Send ACKs (0 for ACK, or frame number for NAK):\n");
        for (int i = 0; i < 4 && frames[i] != 0; i++) {
            int ack;
            printf("ACK for frame %d: ", frames[i]);
            scanf("%d", &ack);
            sprintf(buffer, "%d", ack);
            sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&servaddr, len);
        }
    }

    close(sockfd);
    return 0;
}
