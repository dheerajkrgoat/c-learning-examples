#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <string.h>
#include <stdlib.h>

char buffer[10];

void itoa(int s, char sstr[]) {
    sprintf(sstr, "%d", s);
}

int main() {
    int sockfd, ack;
    char ackstr[10];
    struct sockaddr_in servaddr;
    socklen_t len;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(5382);

    len = sizeof(servaddr);

    // Trigger server to start
    strcpy(buffer, "start");
    sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));

    int ws = 4, n, i;

    while (1) {
        printf("\nReceiving %d packets:\n", ws);
        for (i = 0; i < ws; i++) {
            recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&servaddr, &len);
            n = atoi(buffer);
            printf("Packet %d received\n", n);
        }

        printf("\nEnter acknowledgements for %d packets:\n", ws);
        printf(" - Enter 0 for positive ACK\n");
        printf(" - Enter packet number for NAK (retransmission)\n");

        for (i = 0; i < ws; i++) {
            printf("ACK %d: ", i + 1);
            scanf("%d", &ack);
            itoa(ack, ackstr);
            strcpy(buffer, ackstr);
            sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&servaddr, sizeof(servaddr));
        }
    }

    close(sockfd);
    return 0;
}
