#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int pipefd[2];  // File descriptors for pipe
    pid_t pid1, pid2;

    if (pipe(pipefd) == -1) {  // Create pipe
        perror("Pipe failed");
        exit(1);
    }

    pid1 = fork();  // Create first child

    if (pid1 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid1 == 0) {  // First child process
        close(pipefd[0]);  // Close unused read end
        dup2(pipefd[1], STDOUT_FILENO);  // Redirect stdout to pipe write end
        close(pipefd[1]);  // Close the write end after redirection

        execlp("ls", "ls", NULL);  // Run "ls" command
        perror("execlp failed");
        exit(1);
    }

    pid2 = fork();  // Create second child

    if (pid2 < 0) {
        perror("Fork failed");
        exit(1);
    }

    if (pid2 == 0) {  // Second child process
        close(pipefd[1]);  // Close unused write end
        dup2(pipefd[0], STDIN_FILENO);  // Redirect stdin to pipe read end
        close(pipefd[0]);  // Close the read end after redirection

        execlp("wc", "wc", "-l", NULL);  // Run "wc -l" to count lines
        perror("execlp failed");
        exit(1);
    }

    // Parent process
    close(pipefd[0]);  // Close both pipe ends in parent
    close(pipefd[1]);

    wait(NULL);  // Wait for first child to finish
    wait(NULL);  // Wait for second child to finish

    return 0;
}
