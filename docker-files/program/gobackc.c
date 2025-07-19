#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define MAXLINE 1024

int main() {
    int sockfd;
    char buffer[MAXLINE];
    struct sockaddr_in servaddr;
    socklen_t len = sizeof(servaddr);

    // Create UDP socket
    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // Setup server address
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(PORT);
    servaddr.sin_addr.s_addr = INADDR_ANY;

    // Send initial message to start communication
    strcpy(buffer, "START");
    sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, len);

    int expected = 0;  // Expected frame number

    while (1) {
        int n = recvfrom(sockfd, buffer, MAXLINE, 0, (struct sockaddr *)&servaddr, &len);
        buffer[n] = '\0';

        int frame_no;
        if (sscanf(buffer, "Frame %d", &frame_no) != 1) {
            printf("Invalid frame received.\n");
            continue;
        }

        printf("\nReceived: %s\n", buffer);

        // Ask user to enter ACK manually
        int ack_input;
        printf("Enter ACK to send (expected: %d): ", frame_no);
        scanf("%d", &ack_input);

        // Send entered ACK to server
        sprintf(buffer, "%d", ack_input);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&servaddr, len);

        // Optional: stop after 10 frames are acknowledged in order
        if (ack_input >= 9) break;
    }

    printf("\nTransmission complete (client-side).\n");
    close(sockfd);
return 0;
}

