#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define FRAME_COUNT 10
int main() {
int sock;
struct sockaddr_in serv_addr;
char buffer[1024] = {0};
if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
printf("\n Socket creation error \n");
return -1;
}
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(PORT);
inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr);
for (int frame_number = 0; frame_number < FRAME_COUNT; frame_number++) {
sprintf(buffer, "Frame %d", frame_number);
sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&serv_addr, sizeof(serv_addr));
printf("Sent: %s\n", buffer);
char ack[3];
recvfrom(sock, ack, sizeof(ack), 0, NULL, NULL);
printf("Received: %s\n", ack);
if (frame_number % 3 == 0) {
printf("Simulating loss of Frame %d\n", frame_number);
continue;
}
}
close(sock);
return 0;
}