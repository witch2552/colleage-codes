#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_STUDENTS 10

// Structure for student details
struct Student {
    char name[50];
    int marks;
};

int compare(const void *a, const void *b) {
    return ((struct Student *)b)->marks - ((struct Student *)a)->marks;
}

int main() {
    int n;
    key_t key = ftok("shmfile", 65);
    int shmid = shmget(key, MAX_STUDENTS * sizeof(struct Student), 0666 | IPC_CREAT);
    if (shmid == -1) {
        perror("shmget failed");
        exit(1);
    }

    struct Student *students = (struct Student *)shmat(shmid, NULL, 0);
    if (students == (void *)-1) {
        perror("shmat failed");
        exit(1);
    }

    printf("Enter number of students (max %d): ", MAX_STUDENTS);
    scanf("%d", &n);
    
    for (int i = 0; i < n; i++) {
        printf("Enter name and marks for student %d: ", i + 1);
        scanf("%s %d", students[i].name, &students[i].marks);
    }

    pid_t pid = fork();
    if (pid < 0) {
        perror("fork failed");
        exit(1);
    }

    if (pid == 0) { // Child process
        qsort(students, n, sizeof(struct Student), compare);
        printf("\nRank List:\n");
        for (int i = 0; i < n; i++) {
            printf("Rank %d: %s (Marks: %d)\n", i + 1, students[i].name, students[i].marks);
        }
        shmdt(students);
        exit(0);
    } else { // Parent process
        wait(NULL);
        shmdt(students);
        shmctl(shmid, IPC_RMID, NULL);
    }
    return 0;
}
