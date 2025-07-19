#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>

char buffer[10];

void itoa(int f, char fstr[]) {
    sprintf(fstr, "%d", f);
}

int main() {
    int sockfd, tf, ws;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    int i, next_packet = 1, total_acks = 0;

    char ackstr[10];

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(5382);
    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));

    printf("Waiting for client...\n");
    len = sizeof(cliaddr);
    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);  // wait for "start"

    printf("Enter total number of frames: ");
    scanf("%d", &tf);
    printf("Enter window size: ");
    scanf("%d", &ws);

    int acks[ws], resend[ws];
    int resend_count = 0;

    while (total_acks < tf) {
        // Send window (either new or resend)
        if (resend_count > 0) {
            for (i = 0; i < resend_count; i++) {
                printf("Resending packet %d\n", resend[i]);
                itoa(resend[i], ackstr);
                strcpy(buffer, ackstr);
                sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, len);
            }
        }

        int sent_now = 0;
        while (sent_now < ws - resend_count && next_packet <= tf) {
            printf("Sending packet %d\n", next_packet);
            itoa(next_packet, ackstr);
            strcpy(buffer, ackstr);
            sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, len);
            next_packet++;
            sent_now++;
        }

        // Receive acks for all ws slots
        resend_count = 0;
        for (i = 0; i < ws; i++) {
            recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
            int ack = atoi(buffer);
            if (ack == 0) {
                printf("Positive ACK received\n");
                total_acks++;
            } else {
                printf("NAK received for packet %d\n", ack);
                resend[resend_count++] = ack;
            }
        }
    }

    printf("All packets sent and acknowledged.\n");
    close(sockfd);
    return 0;
}
