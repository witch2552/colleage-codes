#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>

#define PORT 2525
int main(){

    
    int server_fd = socket(AF_INET,SOCK_STREAM,0);
    char buffer[1024] = {0};
    char *response = "message";
    //ADDRESS
    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);
    address.sin_addr.s_addr = INADDR_ANY;

    bind(server_fd,(struct sockaddr *)&address,sizeof(address));

    listen(server_fd,5);

    printf("wait for client");

    int addrlen = sizeof(address);
    int new_socket = accept(server_fd,NULL,NULL);
    read(new_socket,buffer,1024);
    printf("client %s \n",buffer);
    send(new_socket,response,strlen(response),0);
    close(new_socket);
    close(server_fd);

    return 0;
}
