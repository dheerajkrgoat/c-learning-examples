#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<unistd.h>
#include<arpa/inet.h>
#include<net/if.h>
#include<string.h>

char buffer[10];

void itoa(int f, char fstr[]) {
    sprintf(fstr, "%d", f);
}

int main() {
    int sockfd;
    struct sockaddr_in servaddr, cliaddr;
    socklen_t len;
    int tf, ws, i;

    sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = INADDR_ANY;
    servaddr.sin_port = htons(5382);

    bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr));
    printf("\nWaiting for client...");
    len = sizeof(cliaddr);

    recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len); // trigger start

    printf("\nEnter total number of frames: ");
    scanf("%d", &tf);
    printf("Enter window size: ");
    scanf("%d", &ws);

    int p = 1, base = 1, m, num, n;
    char gstr[10], istr[10], nstr[10];
    int a[ws]; // to store NAKs

    for(i = 1; i <= ws && i <= tf; i++) {
        printf("\nSending packet %d", i);
        itoa(i, istr);
        strcpy(buffer, istr);
        sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, len);
    }

    while(p < tf) {
        m = 0;

        for(i = 0; i < ws; i++) {
            recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, &len);
            num = atoi(buffer);

            if(num == 0) {
                printf("\nPositive acknowledgement");
                p++;
            } else {
                a[m] = num;
                m++;
            }
        }

        // Resend only NAKed frames
        for(i = 0; i < m; i++) {
            printf("\nResending packet %d", a[i]);
            itoa(a[i], gstr);
            strcpy(buffer, gstr);
            sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, len);
        }

        // Send new frames if window has space
        for(i = m; i < ws && base + i <= tf; i++) {
            n = base + ws + i - m - 1;
            printf("\nSending packet %d", n);
            itoa(n, nstr);
            strcpy(buffer, nstr);
            sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&cliaddr, len);
        }
    }

    printf("\nAll packets sent\n");
    close(sockfd);
    return 0;
}
