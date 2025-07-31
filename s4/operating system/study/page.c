#include <stdio.h>
#include <stdlib.h>

void fifo(int pages[], int n, int frameSize)
{
    int memory[frameSize];
    int front = 0;
    int pageFault = 0;

    for (int i = 0; i < frameSize; i++)
    {
        memory[i] = -1;
    }

    for (int i = 0; i < n; i++)
    {
        int currentPage = pages[i];
        int found = 0;
             for (int j = 0; j < frameSize; j++){
                if (memory[j] == currentPage){
                    found = 1;
                    break;
                }
             }
             if (!found){
                pageFault++;
                memory[front] = currentPage;
                front = (front + 1) % frameSize;
             }        
    }
                
         printf("Page Faults: %d\nPage Hits: %d\n", pageFault, n-pageFault);           
    }

    void lru(int pages[],int n,int framwsize){
        int memory[framwsize];
        int recentlyused[framwsize];
        int pageFault=0;

        for (int i = 0; i < framwsize; i++)
        {
            memory[i] = -1;
            recentlyused[i] = 0;
        }
        
        for (int i = 0; i < n; i++)
        {
            int currentPage = pages[i];
            int found = 0;
            for (int j = 0; i < framwsize; j++)
            {
                if (memory[j]==currentPage){
                    found=1;
                    recentlyused[j]=i;
                    break;
                }
            }
        if (!found){
            pageFault++;
            int lruindex=0;
            int min=recentlyused[0];
            for (int j = 1; j < framwsize; j++)
            {
                if (recentlyused[j]<min){
                    min=recentlyused[j];
                    lruindex=j;
                }
            }
            memory[lruindex]=currentPage;
            recentlyused[lruindex]=i+1;
        }
    }
                
                
            }
            
    
    

int main()
{
    int n;
    printf("enter the number of pages \n");
    scanf("%d", &n);
    int pages[n];
    for (int i = 0; i < n; i++)
    {
        printf("enter page %d ", i + 1);
        scanf("%d", &pages[i]);
    }
    int frameSize;
    printf("enter the number of frames \n");
    scanf("%d", &frameSize);
    int choice;
    while (1)
    {
        printf("Menu\n");
        printf("1- FIFO\n");
        printf("2- LRU\n");
        printf("3- LFU\n");
        printf("4- Exit\n");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            fifo(pages, n, frameSize);
            break;
        case 2:
            lru(pages, n, frameSize);
            break;
        case 3:
            lfu(pages, n, frameSize);
            break;
        case 4:
            return 0;
        default:
            break;
        }
    }
    return 0;
}