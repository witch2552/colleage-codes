#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define WINDOW_SIZE 4
#define FRAME_COUNT 10
int main() {
int server_fd, new_socket;
struct sockaddr_in address;
int addrlen = sizeof(address);
char buffer[1024] = {0};
int expected_frame = 0;
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
while (expected_frame < FRAME_COUNT) {
recvfrom(server_fd, buffer, sizeof(buffer), 0, (struct sockaddr *)&address,
(socklen_t*)&addrlen);
printf("Received Frame: %s\n", buffer);
if (expected_frame == atoi(buffer + 6)) {
sendto(server_fd, "ACK", strlen("ACK"), 0, (struct sockaddr *)&address, addrlen);
printf("Sent ACK for Frame: %d\n", expected_frame);
expected_frame++;
} else {
printf("Frame %d lost, waiting for retransmission.\n", expected_frame);
}
}
close(server_fd);
return 0;
}