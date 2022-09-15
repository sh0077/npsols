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

    for (;;)
    {
        // sending a message
        bzero(buffer, sizeof(buffer));
        n = 0;
        while ((buffer[n++] = getchar()) != '\n')
            ;
        send(sockFD, buffer, sizeof(buffer), 0);

        // receiving a message
        bzero(buffer, sizeof(buffer));
        recv(sockFD, buffer, sizeof(buffer), 0);
        printf("buffer message is, %s  \n", buffer);

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
    int sockFD = socket(AF_INET, SOCK_STREAM, 0);
    // check sockFD

    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(PORT);
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);

    // connect
    if (connect(sockFD, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) != 0)
    {
        // error
        return 0;
    }
    else
    {
        // pass
        printf("client is started...\n");
    }

    func(sockFD);

    close(sockFD);
}
