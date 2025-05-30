#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define SERVER_IP "127.0.0.1"
#define PORT 8080
#define MAX_CLIENTS 10000
#define MSG_SIZE 64

int main()
{
    for (int i = 0; i < MAX_CLIENTS; i++)
    {
        int sockfd;
        char message[MSG_SIZE];
        snprintf(message, MSG_SIZE, "Client No %d", i + 1);

        if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
        {
            perror("Socket creation failed");
            continue;
        }

        struct sockaddr_in clientaddr;
        memset(&clientaddr, 0, sizeof(clientaddr));
        clientaddr.sin_family = AF_INET;
        clientaddr.sin_port = htons(10001 + i);
        clientaddr.sin_addr.s_addr = INADDR_ANY;

        if (bind(sockfd, (struct sockaddr *)&clientaddr, sizeof(clientaddr)) < 0)
        {
            perror("Bind failed");
            close(sockfd);
            continue;
        }

        struct sockaddr_in servaddr;
        memset(&servaddr, 0, sizeof(servaddr));
        servaddr.sin_family = AF_INET;
        servaddr.sin_port = htons(PORT);
        servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");

        sendto(sockfd, message, strlen(message), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));

        close(sockfd);
    }

    return 0;
}
