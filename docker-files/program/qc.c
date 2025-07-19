// udp_client.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

int main() {
    int sockfd;
    struct sockaddr_in server_addr;
    socklen_t len = sizeof(server_addr);
    int n = 5;
    int received[5], to_send;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(12345);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Send initial dummy message to notify server
    char dummy[1] = {0};
    sendto(sockfd, dummy, sizeof(dummy), 0,
           (struct sockaddr*)&server_addr, len);

    // Step 1: Receive n numbers
    printf("Client received:\n");
    for (int i = 0; i < n; i++) {
        recvfrom(sockfd, &received[i], sizeof(int), 0,
                 (struct sockaddr*)&server_addr, &len);
        printf("Value %d: %d\n", i + 1, received[i]);
    }

    // Step 2: User manually types numbers to send back
    printf("\nEnter %d numbers to send back (can include 0):\n", n);
    for (int i = 0; i < n; i++) {
        printf("Enter number %d: ", i + 1);
        scanf("%d", &to_send);

        sendto(sockfd, &to_send, sizeof(int), 0,
               (struct sockaddr*)&server_addr, len);
    }

    close(sockfd);
    return 0;
}
