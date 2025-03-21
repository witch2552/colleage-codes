#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define FRAME_COUNT 5
int main() {
int server_fd, new_socket;
struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer[1024] = {0};
int frame_number = 0;
if ((server_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
perror("socket failed");
exit(EXIT_FAILURE);
}
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
perror("bind failed");
exit(EXIT_FAILURE);
}
for (frame_number = 0; frame_number < FRAME_COUNT; frame_number++) {
recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&address,
(socklen_t*)&addrlen);
printf("Received Frame: %s\n", buffer);
sendto(server_fd, "ACK", strlen("ACK"), 0, (struct sockaddr *)&address, addrlen);
printf("Sent ACK for Frame: %d\n", frame_number);
}
close(server_fd);
return 0;
}