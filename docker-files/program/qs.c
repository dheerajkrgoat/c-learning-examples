// udp_server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr, client_addr;
    socklen_t len = sizeof(client_addr);
    int n = 5;
    int numbers[] = {11, 22, 33, 44, 55};
    int received;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = INADDR_ANY;

    bind(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));

    // Wait for initial message from client to learn its address
    char init_msg[1];
    recvfrom(sockfd, init_msg, sizeof(init_msg), 0,
             (struct sockaddr*)&client_addr, &len);

    // Step 1: Send n numbers to client
    for (int i = 0; i < n; i++) {
        sendto(sockfd, &numbers[i], sizeof(int), 0,
               (struct sockaddr*)&client_addr, len);
        printf("Sent: %d\n", numbers[i]);
        sleep(1);  // Optional pacing
    }

    // Step 2: Receive n numbers from client
    printf("\nServer receiving back from client:\n");
    for (int i = 0; i < n; i++) {
        recvfrom(sockfd, &received, sizeof(int), 0,
                 (struct sockaddr*)&client_addr, &len);
        printf("Received: %d\n", received);
    }

    close(sockfd);
    return 0;
}
