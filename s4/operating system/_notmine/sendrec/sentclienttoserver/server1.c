#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#define PORT 2525

int main(){
    int server_fd,new_socket ;

    server_fd = socket(AF_INET,SOCK_STREAM,0);
    
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct sockaddr *)&address,sizeof(address));

    listen(server_fd,5);
    printf("listerning to the port %d",PORT);

    socklen_t addr_len = sizeof(address);
    new_socket = accept(server_fd,(struct sockaddr *)&address,&addr_len);

    




    return 0;
}