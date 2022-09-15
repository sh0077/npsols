// 6 libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define PORT 8080

int main()
{
    int sockFD = socket(AF_INET, SOCK_DGRAM, 0);

    // check sockFD
    if(sockFD == -1)
    {
	    printf("error...\n");
    }
    else
    {
	printf("client started...\n");
    }

    // create serverAddress
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    int serverAddrLen = sizeof(serverAddress);

    // func definition thing
    char buffer[256];
    int n;

    for (;;)
    {
        // sending a message
        bzero(buffer, sizeof(buffer));
        n = 0;
        while ((buffer[n++] = getchar()) != '\n')
            ;
        sendto(sockFD, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddress, serverAddrLen);

        // receiving a message
        bzero(buffer, sizeof(buffer));
        recvfrom(sockFD, buffer, sizeof(buffer), 0, (struct sockaddr *)&serverAddress, &serverAddrLen);
        printf("received message: %s \n", buffer);

        // breaking
        if (strncmp(buffer, "exit", 4) == 0)
        {
            printf("exiting now");
            break;
        }
    }

    close(sockFD);
}
