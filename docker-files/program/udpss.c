#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9090
#define MAX_FRAMES 100

int main() {
    int sockfd;
    struct sockaddr_in serverAddr, clientAddr;
    socklen_t addr_len = sizeof(clientAddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    if (bind(sockfd, (struct sockaddr*)&serverAddr, sizeof(serverAddr)) < 0) {
        perror("Bind failed");
        exit(1);
    }

    printf("Server started.\nWaiting for client to start...\n");

    // Wait for client start message
    char start_msg[100];
    recvfrom(sockfd, start_msg, sizeof(start_msg), 0, (struct sockaddr*)&clientAddr, &addr_len);
    printf("Client says: %s\n", start_msg);

    // Ask for user input
    int TOTAL_FRAMES, WINDOW_SIZE;
    printf("Enter total number of frames: ");
    scanf("%d", &TOTAL_FRAMES);
    printf("Enter window size: ");
    scanf("%d", &WINDOW_SIZE);

    int ack[MAX_FRAMES] = {0};
    int base = 0;

    while (base < TOTAL_FRAMES) {
        printf("\n[Server] Sending window:\n");

        for (int i = base; i < base + WINDOW_SIZE && i < TOTAL_FRAMES; i++) {
            if (!ack[i]) {
                sendto(sockfd, &i, sizeof(int), 0, (struct sockaddr*)&clientAddr, addr_len);
                printf("Sent frame: %d\n", i);
            }
        }

        printf("[Server] Waiting for ACKs...\n");

        for (int i = 0; i < WINDOW_SIZE; i++) {
            int recv_ack;
            int n = recvfrom(sockfd, &recv_ack, sizeof(int), 0, (struct sockaddr*)&clientAddr, &addr_len);
            if (n == sizeof(int) && recv_ack >= 0 && recv_ack < TOTAL_FRAMES) {
                if (!ack[recv_ack]) {
                    ack[recv_ack] = 1;
                    printf("Received ACK: %d\n", recv_ack);
                }
            }
        }

        while (ack[base] && base < TOTAL_FRAMES)
            base++;
    }

    printf("\n[Server] All frames sent and acknowledged.\n");
    close(sockfd);
    return 0;
}
