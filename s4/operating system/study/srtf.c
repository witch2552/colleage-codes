#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
typedef struct process{
    int pid;
    int at;
    int bt;
    int wt;
    int tat;
    int rt;
}process;
void srtf(int n,process p[]){
    int time = 0;
    int complete = 0;
    while (complete < n)
    {
        int min_rem = 999;
        int index = -1;
        for (int i = 0; i < n; i++)
        {
            if (p[i].at <= time && p[i].rt < min_rem && p[i].rt > 0)
            {
                min_rem = p[i].rt;
                index = i;
            }
        }
        if (index == -1)
        {
            time++;
            continue;
        }
        p[index].rt--;
        time++;
        
        if (p[index].rt == 0)
        {
            complete++;
            p[index].tat = time - p[index].at;
            p[index].wt = p[index].tat - p[index].bt;
            
        }
        
    }
    
}
int main(){
    return 0;
}