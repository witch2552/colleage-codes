#include <stdio.h>
#include <stdbool.h>

#define MAX_PROCESSES 5
#define MAX_RESOURCES 3

int available[MAX_RESOURCES];
int max[MAX_PROCESSES][MAX_RESOURCES];
int allocation[MAX_PROCESSES][MAX_RESOURCES];
int need[MAX_PROCESSES][MAX_RESOURCES];

void calculateNeed(int processes, int resources) {
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

bool isSafe(int processes, int resources) {
    int work[MAX_RESOURCES];
    bool finish[MAX_PROCESSES] = {false};

    // Copy available resources to work[]
    for (int i = 0; i < resources; i++) {
        work[i] = available[i];
    }

    int safeSequence[MAX_PROCESSES];
    int count = 0;

    while (count < processes) {
        bool found = false;
        for (int i = 0; i < processes; i++) {
            if (!finish[i]) {
                bool possible = true;

                for (int j = 0; j < resources; j++) {
                    if (need[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < resources; j++) {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count++] = i;
                    finish[i] = true;
                    found = true;
                }
            }
        }

        if (!found) {
            printf("The system is in an UNSAFE state!\n");
            return false;
        }
    }

    // Safe sequence found
    printf("The system is in a SAFE state.\nSafe sequence: ");
    for (int i = 0; i < processes; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");

    return true;
}

int main() {
    int processes, resources;

    printf("Enter the number of processes: ");
    scanf("%d", &processes);

    printf("Enter the number of resources: ");
    scanf("%d", &resources);

    printf("Enter the Available resources:\n");
    for (int i = 0; i < resources; i++) {
        scanf("%d", &available[i]);
    }

    printf("Enter the Max resource matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    printf("Enter the Allocation matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Calculate the need matrix
    calculateNeed(processes, resources);

    // Display the Need matrix
    printf("Need matrix:\n");
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < resources; j++) {
            printf("%d ", need[i][j]);
        }
        printf("\n");
    }

    // Check system safety
    isSafe(processes, resources);

    return 0;
}
