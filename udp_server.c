// 6 libraries
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <string.h>

#define PORT 8080

void func(int sockFD)
{
    char buffer[256];
    int n;

    struct sockaddr_in clientAddress;
    int clientAddrLen = sizeof(clientAddress);

    for (;;)
    {
    // receiving a message
        bzero(buffer, sizeof(buffer));
        recvfrom(sockFD, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddress, &clientAddrLen);
        printf("recevived message, %s \n", buffer);
    
    
        // sending a message
        bzero(buffer, sizeof(buffer));
        n = 0;
        while ((buffer[n++] = getchar()) != '\n')
            ;
        sendto(sockFD, buffer, sizeof(buffer), 0, (struct sockaddr *)&clientAddress, clientAddrLen);

        

        // breaking
        if (strncmp(buffer, "exit", 4) == 0)
        {
            printf("exiting now");
            break;
        }
    }
}

int main()
{
    int sockFD = socket(AF_INET, SOCK_DGRAM, 0);

    // check sockFD

    // create serverAddress
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    if (bind(sockFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != 0)
    {
        // error
        return 0;
    }
    else
    {
        // pass
        printf("server started...\n");
    }

    func(sockFD);

    close(sockFD);
}
