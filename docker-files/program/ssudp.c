#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 11225
#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);
    int ack[TOTAL_FRAMES] = {0};

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        exit(EXIT_FAILURE);
    }

    printf("Server started...\n");

    int base = 0;
    while (base < TOTAL_FRAMES) {
        // Send window
        printf("\n[Server] Sending window:\n");
        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!ack[i]) {
                sendto(sockfd, &i, sizeof(int), 0, (struct sockaddr*)&cliaddr, len);
                printf("Sent frame: %d\n", i);
            }
        }

        // Receive ACKs for window
        printf("[Server] Waiting for ACKs...\n");
        for (int i = 0; i < WINDOW_SIZE; i++) {
            int recv_ack;
            int n = recvfrom(sockfd, &recv_ack, sizeof(int), 0, (struct sockaddr*)&cliaddr, &len);
            if (n == sizeof(int) && recv_ack >= 0 && recv_ack < TOTAL_FRAMES) {
                if (!ack[recv_ack]) {
                    printf("Received ACK: %d\n", recv_ack);
                    ack[recv_ack] = 1;
                }
            }
        }

        // Slide window
        while (ack[base] && base < TOTAL_FRAMES) base++;
    }

    printf("\nAll frames sent and acknowledged.\n");
    close(sockfd);
    return 0;
}
