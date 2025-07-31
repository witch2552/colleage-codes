#include <stdio.h>
#include <sys/socket.h>

int socketfd;
int main(){
     socketfd = socket(AF_INET,SOCK_STREAM,0);//socket file descriptor

    struct sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_port = 2000;
    address.sin_addr.s_addr;

    connect(socketfd,address,sizeof(address));

    return 0;
}