#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {  // Child process
        printf("hello\n");
        exit(0);
    } 
    else {  // Parent process
        wait(NULL);  // Parent waits for child to complete
        printf("goodbye\n");
    }

    return 0;
}
