#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <arpa/inet.h>
#define PORT 8085
#define BUFFER_SIZE 1024
int sockfd;
void *receive_messages(void *arg) {
char buffer[BUFFER_SIZE];
int bytes_received;
while ((bytes_received = recv(sockfd, buffer, BUFFER_SIZE, 0)) > 0) {
buffer[bytes_received] = '\0';
printf("%s", buffer);
}
printf("Disconnected from server.\n");
exit(0);
}
int main() {
struct sockaddr_in server_addr;
sockfd = socket(AF_INET, SOCK_STREAM, 0);
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = INADDR_ANY;
connect(sockfd, (struct sockaddr*)&server_addr, sizeof(server_addr));
printf("Connected to chat server. Type messages:\n");
pthread_t thread;
pthread_create(&thread, NULL, receive_messages, NULL);
char message[BUFFER_SIZE];
while (1) {
fgets(message, BUFFER_SIZE, stdin);
send(sockfd, message, strlen(message), 0);
}
close(sockfd);
return 0;
}