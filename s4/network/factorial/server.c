#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 2525

int factorial(int n) {
    int sum = 1;
    for (int i = 1; i <= n; i++) {
        sum = sum * i;
    }
    return sum;
}

int main() {
    int server_fd, new_socket;
    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    bind(server_fd, (struct sockaddr *)&address, sizeof(address));
    listen(server_fd, 5);

    printf("Server is waiting for a client...\n");

    socklen_t addr_len = sizeof(address);
    new_socket = accept(server_fd, (struct sockaddr *)&address, &addr_len);

    int number;
    recv(new_socket, &number, sizeof(number), 0);
    printf("Received number: %d\n", number);
    
    int result = factorial(number);
    send(new_socket, &result, sizeof(result), 0);
    printf("Sent factorial of %d: %d\n", number, result);
        
    close(new_socket);
    close(server_fd);
        
    return 0;
}