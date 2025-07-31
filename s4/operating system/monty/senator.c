#include<stdio.h>
#include<semaphore.h>
#include<pthread.h>
#include<unistd.h>

#define s 5
#define c 3
sem_t hall;

void *senator(void *value)
{   
    int id = *(int *)value;
    while (1)
    {
        printf("senator %d is waiting for the hall\n",id);
        sem_wait(&hall);

        printf("senator %d is in the hall\n",id);
        sleep(1);

        printf("senator %d is leaving the hall\n",id);
        sem_post(&hall);
        sleep(1);
    }
    return NULL;  
}
int main()
{
    pthread_t threads[s];
    int ids[s];
    
    sem_init(&hall,0,c);

    for(int i = 0; i < s; i++) {
        ids[i] = i;
        pthread_create(&threads[i], NULL, senator, &ids[i]);
        }

        for (int i = 0; i < s; i++) {
        pthread_join(threads[i], NULL);
        }
        
    return 0;
}