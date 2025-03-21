#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8081
int main() {
int sockfd = socket(AF_INET, SOCK_STREAM, 0);
struct sockaddr_in serv_addr;
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
serv_addr.sin_addr.s_addr = INADDR_ANY;
connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
char str[100];
printf("Enter string: ");
scanf("%s", str);
write(sockfd, str, strlen(str) + 1);
close(sockfd);
return 0;
}