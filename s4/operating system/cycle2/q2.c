#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
int main() {
    int x = 100;  // Initialize variable

    pid_t pid = fork();  // Create child process

    if (pid < 0) {
        perror("Fork failed");
        exit(1);
    } 
    else if (pid == 0) {  // Child process
        printf("Child: Initial x = %d\n", x);
        x = 200;  // Change value in child
        printf("Child: Changed x = %d\n", x);
    } 
    else {  // Parent process
        printf("Parent: Initial x = %d\n", x);
        x = 300;  // Change value in parent
        printf("Parent: Changed x = %d\n", x);
    }

    return 0;
}
