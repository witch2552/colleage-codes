#include<stdio.h>
void round_robin(int at[],int bt[],int n,int quantum,int rt[],int tat[],int wt[],int response_time[]){
    int time=0 ,completed=0;
    for (int i = 0; i < n; i++)
    {
        rt[i]=bt[i];
        response_time[i]=-1;
    }
    while(completed<n){
        int idle=1;
        for (int i = 0; i < n; i++)
        {
            if (rt[i]>0 && at[i]<=time){
                idle =0;
                if(response_time[i]==-1){
                    response_time[i] = time - at[i];
                }
                if(rt[i]>quantum){
                    time+=quantum;  
                    rt[i]-=quantum;
                }
                else{
                    time+=rt[i];
                    rt[i]=0;
                    completed++;
                    tat[i]=time-at[i];
                    wt[i]=tat[i]-bt[i];
                }
            }
        }
        if (idle==1)
        {
            completed++;
        }
        
    }
}
void printResults(int at[], int bt[], int wt[], int tat[], int response_time[], int n) {
    float total_wt = 0, total_tat = 0;

    printf("\nPID\tAT\tBT\tWT\tTAT\tRT\n");
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
        printf("%d\t%d\t%d\t%d\t%d\t%d\n", i+1, at[i], bt[i], wt[i], tat[i], response_time[i]);
    }

    printf("\nAverage Waiting Time: %.2f", total_wt / n);
    printf("\nAverage Turnaround Time: %.2f\n", total_tat / n);
}
int main(){
    int n,quantum;
    printf("enter number of processes\n");
    scanf("%d",&n);
    printf("enter quantum\n");  
    scanf("%d",&quantum);
    int at[n],bt[n],rt[n],tat[n],wt[n],response_time[n];
    for(int i=0;i<n;i++){
        printf("enter arrival time and burst time  %d:",i+1);
        scanf("%d %d",&at[i],&bt[i]);
    }
    round_robin(at,bt,n,quantum,rt,tat,wt,response_time);
    printResults(at, bt, wt, tat, response_time, n);
    return 0;
}