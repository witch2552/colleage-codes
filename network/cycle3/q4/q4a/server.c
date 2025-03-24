#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8081
void reverseString(char *str)
{
    int len = strlen(str);
    for (int i = 0; i < len / 2; i++)
    {
        char temp = str[i];
        str[i] = str[len - i - 1];
        str[len - i - 1] = temp;
    }
}
int main()
{
    int sockfd, client1, client2;
    struct sockaddr_in serv_addr;
    char buffer[1024];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(PORT);
    bind(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
    listen(sockfd, 2);
    client1 = accept(sockfd, NULL, NULL);
    client2 = accept(sockfd, NULL, NULL);
    read(client1, buffer, sizeof(buffer));
    reverseString(buffer);
    write(client2, buffer, strlen(buffer) + 1);
    close(client1);
    close(client2);
    close(sockfd);
    return 0;
}