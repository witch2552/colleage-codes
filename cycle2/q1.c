#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid = fork();

    if (pid < 0)
    {
        perror("Fork failed");
        exit(1);
    }
    else if (pid == 0)
    {
        printf("Child Process: PID = %d\n", getpid());
        exit(0);
    }
    else
    {
        wait(NULL); // Parent waits for child
        printf("Parent Process: PID = %d\n", getpid());
    }

    return 0;
}
