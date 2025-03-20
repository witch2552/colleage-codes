#include <stdio.h>

#define MAX_BLOCKS 10

void firstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];

    // Initialize all allocations as -1 (unallocated)
    for (int i = 0; i < processes; i++)
        allocation[i] = -1;

    // First fit algorithm
    for (int i = 0; i < processes; i++) {
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                allocation[i] = j;    // Allocate block j to process i
                blockSize[j] -= processSize[i]; // Reduce available size in block
                break; // Stop searching once the first suitable block is found
            }
        }
    }

    // Display results
    printf("Process No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int blockSize[MAX_BLOCKS], processSize[MAX_BLOCKS];
    int blocks, processes;

    printf("Enter the number of memory blocks: ");
    scanf("%d", &blocks);
    printf("Enter the sizes of the memory blocks: ");
    for (int i = 0; i < blocks; i++) {
        scanf("%d", &blockSize[i]);
    }

    printf("Enter the number of processes: ");
    scanf("%d", &processes);
    printf("Enter the sizes of the processes: ");
    for (int i = 0; i < processes; i++) {
        scanf("%d", &processSize[i]);
    }

    firstFit(blockSize, blocks, processSize, processes);

    return 0;
}
