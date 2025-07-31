#include <stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/wait.h>

int main(){
    pid_t pid = fork();
    if (pid == -1){
        printf("error\n");
    }
    else if (pid == 0){
        printf("child process%d\n",getpid());
        exit(1);
    }
    else
    {
        wait(NULL);
        printf("parent process%d\n",getpid());
        /* code */
    }
 return 0;   
}