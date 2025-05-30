#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/fcntl.h>
#include <time.h>
#include <poll.h>

#define PORT 8080
#define MAX_LINE 1024

int main()
{
    int sockfd;

    struct sockaddr_in servaddr, cliaddr;

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
        fd_set readfds;           // File descriptor set for select
        FD_ZERO(&readfds);        // Set the file descriptor set to zero
        FD_SET(sockfd, &readfds); // Add the socket file descriptor to the set

        struct timeval timeout; // Timeout structure for select
        timeout.tv_sec = 5;     // Set timeout to 5 seconds
        timeout.tv_usec = 0;    // Set microseconds to 0

        int act = select(sockfd + 1, &readfds, NULL, NULL, &timeout);

        if (act < 0)
        {
            perror("error");
            break;
        }
        else if (act == 0)
        {
            perror("No data in 5 sec");
            break;
        }

        if (FD_ISSET(sockfd, &readfds))
        {
            int len = sizeof(cliaddr);
            int n = recvfrom(sockfd, buffer, MAX_LINE, 0, (struct sockaddr *)&cliaddr, &len);

            if (n < 0)
            {
                perror("No data recieved");
            }
            else
            {
                buffer[n] = '\0';
                int port = ntohs(cliaddr.sin_port);
                printf("%s - %d\n", buffer, port);
            }
        }
    }

    close(sockfd);

    return 0;
}
