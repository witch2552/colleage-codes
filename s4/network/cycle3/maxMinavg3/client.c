#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
int main() {

int sock = socket(AF_INET, SOCK_STREAM, 0);

struct sockaddr_in server_addr;
server_addr.sin_family = AF_INET;
server_addr.sin_port = htons(PORT);
server_addr.sin_addr.s_addr = INADDR_ANY;

connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr));

int max, min;
float avg;
read(sock, &max, sizeof(max));
read(sock, &min, sizeof(min));
read(sock, &avg, sizeof(avg));
// Display the results
printf("Max: %d, Min: %d, Avg: %.2f\n", max, min, avg);
close(sock);
return 0;
}