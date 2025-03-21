#include <stdio.h>

int main() {
    int n, i;
    int at[20], bt[20], wt[20], tat[20], ct[20], total_wt = 0, total_tat = 0;
    float avg_wt, avg_tat;

    // Input: Number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    // Input: Arrival Time & Burst Time
    printf("\nEnter Arrival Time and Burst Time:\n");
    for (i = 0; i < n; i++) {
        printf("P%d Arrival Time: ", i + 1);
        scanf("%d", &at[i]);
        printf("P%d Burst Time: ", i + 1);
        scanf("%d", &bt[i]);
    }

    // Calculate Completion Time (CT)
    int start_time = 0;
    for (i = 0; i < n; i++) {
        if (start_time < at[i]) // If CPU is idle, wait until process arrives
            start_time = at[i];
        ct[i] = start_time + bt[i]; // Completion Time = Start Time + Burst Time
        start_time = ct[i]; // Update Start Time
    }

    // Calculate Turnaround Time (TAT) and Waiting Time (WT)
    for (i = 0; i < n; i++) {
        tat[i] = ct[i] - at[i]; // TAT = Completion Time - Arrival Time
        wt[i] = tat[i] - bt[i]; // WT = Turnaround Time - Burst Time
        total_wt += wt[i];
        total_tat += tat[i];
    }

    // Display Results
    printf("\nProcess\tArrival Time\tBurst Time\tWaiting Time\tTurnaround Time");
    for (i = 0; i < n; i++) {
        printf("\nP%d\t\t%d\t\t%d\t\t%d\t\t%d", i + 1, at[i], bt[i], wt[i], tat[i]);
    }

    // Compute Averages
    avg_wt = (float)total_wt / n;
    avg_tat = (float)total_tat / n;
    
    printf("\n\nAverage Waiting Time = %.2f", avg_wt);
    printf("\nAverage Turnaround Time = %.2f\n", avg_tat);

    return 0;
}
