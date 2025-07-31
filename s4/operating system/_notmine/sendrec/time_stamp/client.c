#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <time.h>
int main()
{
    int sock, bytes, i;
    if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
        printf("Socket Creation Failed\nExiting...\n");
        return 0;
    }
    printf("Socket Created\n");
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(8880);
    while (1)
    {
        printf("Do you want to get current time [y/n]: ");
        char c[1];
        scanf("%s", c);
        if (c[0] == 'y')
        {
            i = 1;
            if ((bytes = sendto(sock, &i, sizeof(i), 0, (struct sockaddr *)&address, (socklen_t)sizeof(address))) < 0)
            {
                printf("Sending Failed\nExiting....\n");
                return 0;
            }
            time_t seconds;
            if ((bytes = recvfrom(sock, &seconds, sizeof(seconds), 0, NULL, NULL)) < 0)
            {
                printf("Receiving Failed\nExiting....\n");
                return 0;
            }
            printf("The Time received is %d\n", seconds);
        }
        else
        {
            i = 0;
            if ((bytes = sendto(sock, &i, sizeof(i), 0, (struct sockaddr *)&address, (socklen_t)sizeof(address))) < 0)
            {
                printf("Sending Failed\nExiting....\n");
                return 0;
            }
            printf("Exiting....\n");
            return 0;
        }
    }
    return 0;
}