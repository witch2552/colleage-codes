#include<stdio.h>
#include<stdlib.h>

void fcfs(int requests[],int n,int head){
    int seek_time = 0;
    for (int i = 0; i < n; i++)
    {   
        seek_time += abs( head - requests[i]);
        head = requests[i];
        /* code */
    }
    printf("total seek time : %d",seek_time);
    
}
int main(){
    int n , head;
    printf("Enter the number of disk requests: ");
    scanf("%d",&n);
    int requests[n];
    printf("enter the disk requests: ");
    for(int i =0;i<n;i++){
        scanf("%d",&requests[i]);
    }
    printf("Enter the head position: ");
    scanf("%d",&head);
    
    fcfs(requests,n,head);
    return 0;
}