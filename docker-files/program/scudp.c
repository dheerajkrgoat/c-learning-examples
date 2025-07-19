#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>

#define PORT 11225
#define WINDOW_SIZE 4
#define TOTAL_FRAMES 10

int main() {
    int sockfd;
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    int received[WINDOW_SIZE];  // Store received frames per window

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    printf("Client started...\n");

    int total = 0;

    while (total < TOTAL_FRAMES) {
        printf("\n[Client] Receiving window of frames...\n");
        int count = 0;

        // Receive a full window
        while (count < WINDOW_SIZE && total + count < TOTAL_FRAMES) {
            int frame;
            int n = recvfrom(sockfd, &frame, sizeof(int), 0, (struct sockaddr*)&servaddr, &len);
            if (n == sizeof(int)) {
                printf("Received frame: %d\n", frame);
                received[count++] = frame;
            }
        }

        // Manual ACK entry
        for (int i = 0; i < count; i++) {
            int ack;
            printf("Enter ACK for frame %d (enter same number to ACK or -1 to skip): ", received[i]);
            scanf("%d", &ack);
            if (ack == received[i]) {
                sendto(sockfd, &ack, sizeof(int), 0, (struct sockaddr*)&servaddr, len);
                printf("ACK %d sent\n", ack);
                total++;
            } else {
                printf("ACK skipped for frame %d\n", received[i]);
            }
        }
    }

    printf("\nAll frames received.\n");
    close(sockfd);
    return 0;
}
