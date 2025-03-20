#include <stdio.h>

#define MAX_BLOCKS 10

void worstFit(int blockSize[], int blocks, int processSize[], int processes) {
    int allocation[processes];

    // Initialize all allocations as -1 (unallocated)
    for (int i = 0; i < processes; i++)
        allocation[i] = -1;

    // Worst fit algorithm
    for (int i = 0; i < processes; i++) {
        int worstIdx = -1;
        for (int j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (worstIdx == -1 || blockSize[j] > blockSize[worstIdx]) {
                    worstIdx = j;
                }
            }
        }

        // If found a suitable block
        if (worstIdx != -1) {
            allocation[i] = worstIdx;    // Allocate block j to process i
            blockSize[worstIdx] -= processSize[i]; // Reduce available size in block
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

    // Fragmentation check
    int totalFragmentation = 0;
    for (int i = 0; i < blocks; i++) {
        totalFragmentation += blockSize[i];
    }

    printf("\nTotal Unused Memory (Fragmentation): %d\n", totalFragmentation);
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

    worstFit(blockSize, blocks, processSize, processes);

    return 0;
}
