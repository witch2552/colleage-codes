#include<stdio.h>
void fcfs(int n,int at[],int bt[]){
    int ct[20],tat[20],wt[20];
    int st;
    st=0;
    for (int i = 0; i < n; i++)
    {
        /* code */
        if (st<at[i])
        {
            st=at[i];
        }
    ct[i]=st+bt[i];
    st=ct[i];    
    }
    int total_tat=0;
    int total_wt=0;
    for (int i = 0; i < n; i++)
    {
        /* code */tat[i]=ct[i]-at[i];
        wt[i]=tat[i]-bt[i]; 
        total_tat+=tat[i];
        total_wt+=wt[i];
    }
    
    printf("process\tarrival time\tburst time\tcompletion time\tturn around time\twaiting time\n");
    for (int i = 0; i < n; i++)
    {
    printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\t\t%d\n",i+1,at[i],bt[i],ct[i],tat[i],wt[i]);
    }
    printf("average turn around time=%d\n",total_tat/n);
    printf("average waiting time=%d\n",total_wt/n);
}

void round_robin(int n,int at[],int bt[]){

}

void sjf(int n,int at[],int bt[]){
    int pos,temp;
    for (int i = 0; i < n-1; i++)
    {
        /* code */for (int j = i+1; j < n; j++)
        {
            /* code */
        }
        
    }
    
}
int main(){
    int at[20],bt[20];
    int n;
    printf("enter the number of processes\n");
    scanf("%d",&n);
    for (int i = 0; i < n; i++)
    {
        printf("enter the arrival time and burst time %d ",i+1);
        scanf("%d %d",&at[i],&bt[i]);
        
    }
    
    fcfs(n,at,bt);
                                                                                                                                            
    
    return 0;
}