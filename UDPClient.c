#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/fcntl.h>

#define PORT 8080
#define MAX_LINE 1024

int main()
{
    int sockfd;
    char *message = "Client Message";

    struct sockaddr_in servaddr;

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) // Create a new socket, in UDP use SOCK_DGRAM(datagram) for type
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(sockfd, F_GETFL, 0);
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK);

    memset(&servaddr, 0, sizeof(servaddr)); // Server IP

    servaddr.sin_family = AF_INET;         // Holds IP address
    servaddr.sin_port = htons(PORT);       // htons -> convert values between host and network byte order
    servaddr.sin_addr.s_addr = INADDR_ANY; // Accepts connections to all the IPs

    sendto(sockfd, message, strlen(message), MSG_CONFIRM, (struct sockaddr *)&servaddr, sizeof(servaddr));

    char buffer[MAX_LINE];

    while (1)
    {
        int len = sizeof(servaddr); // Length of the server address structure
        int n = recvfrom(sockfd, buffer, MAX_LINE, 0, (struct sockaddr *)&servaddr, &len);

        if (n < 0)
        {
            printf("Waiting for data...\n");
            sleep(5);
        }
        else
        {
            buffer[n] = '\0'; // End of the data
            printf("Server says: %s\n", buffer);
            break; // Exit after receiving a message
        }
    }

    close(sockfd);

    return 0;
}