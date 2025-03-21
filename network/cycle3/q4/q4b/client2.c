#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8082
int main() {
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = INADDR_ANY;
connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
int squared;
read(sockfd, &squared, sizeof(squared));
printf("Received squared value: %d\n", squared);
close(sockfd);
return 0;
}