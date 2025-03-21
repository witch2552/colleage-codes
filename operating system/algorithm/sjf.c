#include <stdio.h>

int main() {
    int n, i, j, pos, temp;
    int bt[20], p[20], wt[20], tat[20], total_wt = 0, total_tat = 0;
    float avg_wt, avg_tat;

    // Input: Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input: Burst Time
    printf("\nEnter Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d: ", i + 1);
        scanf("%d", &bt[i]);
        p[i] = i + 1; // Store process number
    }

    // Sorting by Burst Time (Selection Sort)
    for (i = 0; i < n - 1; i++){
        pos = i;
        for (j = i + 1; j < n; j++) {
            if (bt[j] < bt[pos]) {
                pos = j;
            }
        }
        // Swap Burst Time
        temp = bt[i];
        bt[i] = bt[pos];
        bt[pos] = temp;

        // Swap Process ID
        temp = p[i];
        p[i] = p[pos];  
        p[pos] = temp;
    }

    // Compute Waiting Time
    wt[0] = 0; // First process has zero waiting time
    for (i = 1; i < n; i++) {
        wt[i] = wt[i - 1] + bt[i - 1];
        total_wt += wt[i]; // Total waiting time
    }

    // Compute Turnaround Time
    for (i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
        total_tat += tat[i]; // Total turnaround time
    }

    // Display Results
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t\t%d\t\t%d\t\t%d", p[i], bt[i], wt[i], tat[i]);
    }

    // Compute Averages
    avg_wt = (float)total_wt / n;
    avg_tat = (float)total_tat / n;

    printf("\n\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
