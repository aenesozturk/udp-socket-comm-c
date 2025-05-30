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
    struct sockaddr_in servaddr, cliaddr;
    char *message = "Server Message";

    if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) // Create a new socket, in UDP use SOCK_DGRAM(datagram) for type
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    int flags = fcntl(sockfd, F_GETFL, 0);      // Get the current flags of the socket
    fcntl(sockfd, F_SETFL, flags | O_NONBLOCK); // Set the socket to non-blocking mode

    memset(&servaddr, 0, sizeof(servaddr)); // Server IP
    memset(&cliaddr, 0, sizeof(cliaddr));   // Client IP

    servaddr.sin_addr.s_addr = INADDR_ANY; // Holds IP address
    servaddr.sin_port = htons(PORT);       // htons -> convert values between host and network byte order
    servaddr.sin_family = AF_INET;         // Accepts connections to all the IPs

    if (bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) // Assings the address to the unbound socket
    {
        perror("Socket bind failed");
        close(sockfd);
        exit(EXIT_FAILURE);
    }

    char buffer[MAX_LINE];

    while (1)
    {
        int len = sizeof(cliaddr); // Length of the client address structure
        int n = recvfrom(sockfd, buffer, MAX_LINE, 0, (struct sockaddr *)&cliaddr, &len);

        if (n < 0)
        {
            printf("Waiting for data...\n");
            sleep(5);
        }
        else
        {
            buffer[n] = '\0'; // End of the data
            printf("Client says: %s\n", buffer);

            sendto(sockfd, message, strlen(message), MSG_CONFIRM, (struct sockaddr *)&cliaddr, sizeof(cliaddr));
            break; // Exit after sending a message
        }
    }

    return 0;
}
