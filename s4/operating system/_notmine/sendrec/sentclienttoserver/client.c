#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<string.h>
#define PORT 2525
int main(){
    int sock = 0;

    char *message = "hello";
    char buffer[1024] ={0};
    
    sock = socket(AF_INET,SOCK_STREAM,0);

    //address
    struct sockaddr_in serv_addr;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    send(sock,message,strlen(message),0);
    read(sock,buffer,1024);
    printf("server %s \n",buffer);

    close(sock);

    return 0;
}