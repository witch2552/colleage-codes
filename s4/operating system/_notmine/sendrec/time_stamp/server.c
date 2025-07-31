#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
int main()
{
    int sock, i, bytes;

    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Socket Creation Failed\nExiting...\n");
        return 0;
    }

    printf("Socket Created\n");

    struct sockaddr_in address, client_addr;
    address.sin_family = AF_INET;
    address.sin_port = htons(8880);
    address.sin_addr.s_addr = INADDR_ANY;\
    
    socklen_t addrlen = sizeof(struct sockaddr);

    if ((bind(sock, (struct sockaddr *)&address, sizeof(address))) < 0)
    {
        printf("Binding Failed\nExiting....\n");
        return 0;
    }

    printf("Server Binded\n");

    while (1)
    {
        if ((bytes = recvfrom(sock, &i, sizeof(i), 0, (struct sockaddr *)&client_addr,
                              (socklen_t *)&addrlen)) < 0)
        {
            printf("Receiving Failed\nExiting....\n");
            return 0;
        }

        if (i == 1)
        {
            time_t seconds;
            seconds = time(NULL);
            if ((bytes = sendto(sock, &seconds, sizeof(seconds), 0, (struct sockaddr *)&client_addr, addrlen) < 0))
            {
                printf("Sending Failed\nExiting....\n");
                return 0;
            }

            printf("Current time sent\n");
        }
        else
        {
            printf("Exiting....\n");
        }
    }
    return 0;
}