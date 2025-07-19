#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 9090
#define MAX_FRAMES 100

int main() {
    int sockfd;
    struct sockaddr_in serverAddr;
    socklen_t addr_len = sizeof(serverAddr);

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd < 0) {
        perror("Socket creation failed");
        exit(1);
    }

    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = INADDR_ANY;

    printf("Client started.\nSending start message to server...\n");
    char msg[] = "Client is ready!";
    sendto(sockfd, msg, sizeof(msg), 0, (struct sockaddr*)&serverAddr, addr_len);

    int received[MAX_FRAMES] = {0};
    int TOTAL_FRAMES, WINDOW_SIZE;

    printf("Enter total number of frames (same as server): ");
    scanf("%d", &TOTAL_FRAMES);
    printf("Enter window size (same as server): ");
    scanf("%d", &WINDOW_SIZE);

    int total = 0;

    while (total < TOTAL_FRAMES) {
        printf("\n[Client] Receiving window...\n");

        int window[WINDOW_SIZE];
        int count = 0;

        while (count < WINDOW_SIZE && total + count < TOTAL_FRAMES) {
            int frame;
            int n = recvfrom(sockfd, &frame, sizeof(int), 0, (struct sockaddr*)&serverAddr, &addr_len);
            if (n == sizeof(int)) {
                printf("Received frame: %d\n", frame);
                window[count++] = frame;
            }
        }

        for (int i = 0; i < count; i++) {
            int ack_input;
            printf("Enter ACK for frame %d (same number to ACK, or -1 to skip): ", window[i]);
            scanf("%d", &ack_input);

            if (ack_input == window[i]) {
                sendto(sockfd, &ack_input, sizeof(int), 0, (struct sockaddr*)&serverAddr, addr_len);
                printf("Sent ACK: %d\n", ack_input);
                received[ack_input] = 1;
                total++;
            } else {
                printf("Skipped ACK for frame %d\n", window[i]);
            }
        }
    }

    printf("\n[Client] All frames received and acknowledged.\n");
    close(sockfd);
    return 0;
}
