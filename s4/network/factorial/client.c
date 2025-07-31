#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#define PORT 2525

int main(){
    int sock;
    sock=socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in serv_addr;
    serv_addr.sin_family=AF_INET;
    serv_addr.sin_port = htons(PORT);
    serv_addr.sin_addr.s_addr = INADDR_ANY;

    connect(sock,(struct sockaddr *)&serv_addr,sizeof(serv_addr));

    int num;
    printf("Enter an integer: ");
    scanf("%d",&num);
    send(sock,&num,sizeof(num),0);

    int sum;
    recv(sock,&sum,sizeof(sum),0);
    printf("Factorial of %d is %d\n",num,sum);
    close(sock);    

    return 0;

}