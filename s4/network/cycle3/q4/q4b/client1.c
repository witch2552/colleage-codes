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
int num;
printf("Enter an integer: ");
scanf("%d", &num);
write(sockfd, &num, sizeof(num));
close(sockfd);
return 0;
}