#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 8080
#define MAX_SIZE 100
int main() {
int server_fd, new_socket, nums[MAX_SIZE], n;
struct sockaddr_in address;
socklen_t addr_len = sizeof(address);
server_fd = socket(AF_INET, SOCK_STREAM, 0);
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;
address.sin_port = htons(PORT);
bind(server_fd, (struct sockaddr*)&address, sizeof(address));
listen(server_fd, 5);
printf("Server listening on port %d...\n", PORT);
new_socket = accept(server_fd, (struct sockaddr*)&address, &addr_len);
printf("Enter number of elements: ");
scanf("%d", &n);
printf("Enter elements: ");
for (int i = 0; i < n; i++) {
scanf("%d", &nums[i]);
}
int max = nums[0], min = nums[0], sum = 0;
for (int i = 0; i < n; i++) {
if (nums[i] > max) max = nums[i];
if (nums[i] < min) min = nums[i];
sum += nums[i];
}
float avg = (float)sum / n;
write(new_socket, &max, sizeof(max));
write(new_socket, &min, sizeof(min));
write(new_socket, &avg, sizeof(avg));
printf("Results sent to client.\n");
close(new_socket);
close(server_fd);
return 0;
}