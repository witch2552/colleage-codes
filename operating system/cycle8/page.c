#include <stdio.h>
#include <limits.h>
int ispageinFrames(int frames[],int page,int f){
    for (int i = 0 ; i < f ; i++){
        if (frames[i]==page){
            return i;
        }
    }
    return -1;
}
void fifo(int pages[], int p, int f)
{
    int front = 0, faults = 0, hits = 0,flag=0,frames[f];
    for (int i = 0; i < f ; i++)
    {
        frames[i] = -1;
    }
    printf("First in first out\n");
    printf("Page       Frames\n");
    for (int i = 0; i < p; i++)
    {
        printf("%d          ",pages[i]);
        int check =ispageinFrames(frames, pages[i], f);
        if(check!=-1){
            hits++;
            flag=0;    
        }
        else{
            frames[front]=pages[i];
            front=(front+1)%f;
            faults++;
            flag=1;
        }
        display(frames,f,flag);
    }
    printf("\nTotal Page Faults: %d\n", faults);
    printf("Total Page Hits: %d\n", hits);
}
int findIndex(int lasthit[],int f){
    int min= lasthit[0],index=0;
    for(int i =1;i<f;i++){
        if(lasthit[i]<min){
            index=i;
            min=lasthit[i];
        }
    }
    return index;
}
void lru(int pages[], int p, int f)
{
    int faults = 0, hits = 0,flag=0,frames[f], lasthit[f],time=0;   
    for (int i = 0; i < f; i++)
    {
        frames[i] = -1;
        lasthit[i] = 0;
    }
    printf("Least Recently Used \n");
    printf("Page       Frames\n");
    for (int i = 0; i < p; i++)
    {   time++;
        printf("%d          ", pages[i]);
        int check =ispageinFrames(frames, pages[i], f);
        if (check!=-1)
        {
            hits++;
            lasthit[check]=time;
            flag=0;
        }
        else
        {
            int index=findIndex(lasthit,f);
            frames[index]=pages[i];
            lasthit[index]=time;
            faults++;
            flag=1;           
        }
        display(frames,f,flag);
    }
    printf("\nTotal Page Faults: %d\n", faults);
    printf("Total Page Hits: %d\n", hits);
}
int findIndexlfu(int frequency[],int age[],int f){
    int min= INT_MAX,index=0,oldest=INT_MAX;
    for(int i =0;i<f;i++){
        if(frequency[i]<min || (frequency[i]==min && age[i]<oldest)){
            index=i;
            oldest=age[i];
            min=frequency[i];
        }
    }
    return index;
}
void lfu(int pages[], int p, int f)
{
    int faults = 0, hits = 0,flag=0;
    int frames[f], frequency[f],age[f];
    int time=0;
    
    for (int i = 0; i < f; i++)
    {
        frames[i] = -1;
        frequency[i] = 0;
        age[i]=0;
    }
    printf("Page       Frames\n");
    for (int i = 0; i < p; i++)
    {   time++;
        printf("%d          ", pages[i]);
        int check =ispageinFrames(frames, pages[i], f);
        if (check!=-1)
        {
            hits++;
            frequency[check]++;
            flag=0;
        }
        else
        {
            int index=findIndexlfu(frequency,age,f);
            frames[index]=pages[i];
            frequency[index]=1;
            age[index]=time;
            faults++;
            flag=1;           
        }
        display(frames,f,flag);
    }
    printf("\nTotal Page Faults: %d\n", faults);
    printf("Total Page Hits: %d\n", hits);
}
int optimalIndex(int pages[], int frames[], int p, int f, int currentIndex)
{
    int returnindex = -1, farthestIndex = currentIndex;
    for (int i = 0; i < f; i++)
    {
        int j;
        for (j = currentIndex; j < p; j++)
        {
            if (frames[i] == pages[j])
            {
                if (j > farthestIndex)
                {
                    farthestIndex = j;
                    returnindex = i;
                }
                break;
            }
        }
        if(j==p){
            return i;
        }
    }
    return returnindex;
}
void optimal(int pages[], int p, int f)
{
    int faults = 0, hits = 0, flag = 0;
    int frames[f], lasthit[f];

    for (int i = 0; i < f; i++)
    {
        frames[i] = -1;
        lasthit[i] = 0;
    }
    printf("Page       Frames\n");
    for (int i = 0; i < p; i++)
    {
        printf("%d          ", pages[i]);
        int check = ispageinFrames(frames, pages[i], f);
        if (check != -1)
        {
            hits++;
            flag = 0;
        }
        else
        {
            int index = -1;
            for (int j = 0; j < f; j++)
            {
                if (frames[j] == -1)
                {
                    index = j;
                    break;
                }
            }
            if (index == -1)
            {
                index = optimalIndex(pages, frames, p, f, i);
            }
            frames[index] = pages[i];
            faults++;
            flag = 1;
        }
        display(frames,f,flag);
        
    }
    printf("\nTotal Page Faults: %d\n", faults);
    printf("Total Page Hits: %d\n", hits);
}
void display(int frames[],int f,int flag){
    for (int j = 0; j < f; j++)
            {
                if (frames[j] != -1)
                {
                    printf("%d  ", frames[j]);
                }
                else
                {
                    printf("   ");
                }
            }
            if(flag==1){
                printf("   Fault\n");
            }
            else{
                printf("   Hit\n");
            }
}
int main()
{
    int p, f,choice;
    printf("Enter the number of frames : ");
    scanf("%d", &f);
    printf("Enter the number of pages : ");
    scanf("%d", &p);
    printf("Enter all the pages in order \n");
    int pages[p];
    for (int i = 0; i < p; i++)
    {
        scanf("%d", &pages[i]);
    }
    while(1){
        printf("Enter choice : \n1:FIFO\n2:LRU\n3:LFU\n4:Optimal\n");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                fifo(pages,p,f);
                break;
            case 2:
                lru(pages,p,f);
                break;
            case 3:
                lfu(pages,p,f);
                break;
            case 4:
                optimal(pages,p,f);
            default:
                return 0;
        }
    }  
    return 0;
}