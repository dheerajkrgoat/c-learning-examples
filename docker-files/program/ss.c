#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 1234
#define MAX_FRAMES 100
#define BUFFER_SIZE 1024

int main() {
    int sockfd, totalFrames, windowSize, i;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    char buffer[BUFFER_SIZE];
    int ack[MAX_FRAMES] = {0};

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("socket creation failed");
        exit(1);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("bind failed");
        exit(1);
    }

    printf("Waiting for client...\n");
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len); // receive "start"
    printf("Client connected.\n");

    printf("Enter total number of frames: ");
    scanf("%d", &totalFrames);
    printf("Enter window size: ");
    scanf("%d", &windowSize);

    int nextFrame = 1;

    while (1) {
        // Send up to windowSize frames
        int sentInThisRound = 0;
        for (i = 0; i < windowSize && nextFrame + i <= totalFrames; i++) {
            int frame = nextFrame + i;
            if (ack[frame] == 0) {
                sprintf(buffer, "%d", frame);
                sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, len);
                printf("Sent frame: %d\n", frame);
                sentInThisRound++;
            }
        }

        // Receive ACKs
        for (i = 0; i < sentInThisRound; i++) {
            recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);
            int response = atoi(buffer);
            if (response == 0) {
                printf("ACK for frame %d\n", nextFrame);
                ack[nextFrame] = 1;
                nextFrame++;
            } else {
                printf("NAK for frame %d\n", response);
                ack[response] = 0;
            }
        }

        // Check if all frames ACKed
        int allAcked = 1;
        for (i = 1; i <= totalFrames; i++) {
            if (ack[i] == 0) {
                allAcked = 0;
                break;
            }
        }

        if (allAcked) {
            printf("All frames sent and acknowledged.\n");
            break;
        }
    }

    close(sockfd);
    return 0;
}
