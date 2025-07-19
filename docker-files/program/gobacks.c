#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024
#define TOTAL_FRAMES 10
#define WINDOW_SIZE 4

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len = sizeof(cliaddr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Setup server address
    memset(&servaddr, 0, sizeof(servaddr));
    memset(&cliaddr, 0, sizeof(cliaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(PORT);

    // Bind socket
    if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) {
        perror("Bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    printf("Server waiting for client to initiate transmission...\n");

    // Wait for client to start
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);

    int base = 0;

    while (base < TOTAL_FRAMES) {
        int end = base + WINDOW_SIZE;
        if (end > TOTAL_FRAMES) end = TOTAL_FRAMES;

        printf("\nSending frames from %d to %d\n", base, end - 1);
        for (int i = base; i < end; i++) {
            sprintf(buffer, "Frame %d", i);
            sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&cliaddr, len);
            printf("Sent: %s\n", buffer);
        }

        // Receive ACK from client
        recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, &len);
        buffer[strcspn(buffer, "\n")] = 0;  // remove newline if present
        int ack = atoi(buffer);
        printf("Received ACK: %d\n", ack);

        if (ack >= end - 1) {
            // If ACK for last frame in window, slide window forward
            base = ack + 1;
        } else {
            // Go back to the frame after last correct one
            printf("Go-Back-N: Resending from frame %d\n", ack + 1);
            base = ack + 1;
        }
    }

    printf("\nAll frames sent and acknowledged.\n");
    close(sockfd);
return 0;
}

