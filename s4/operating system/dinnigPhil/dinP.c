#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define n 5
sem_t forks[n];
sem_t eat;

void *philospher(void*value){
    int id = *(int*)value;
    while (1)
    {
        printf("philospher %d thinking \n",id);
        sleep(1);

        sem_wait(&eat);
        sem_wait(&forks[id]);
        sem_wait(&forks[(id+1)%n]);
        printf("philospher is eating");
        sleep(1);
        /* code */
        sem_post(&forks[id]);
        sem_post(&forks[(id+1)%n]);
        sem_post(&eat);

    }   
    return NULL;
}
int main(){
    
    pthread_t threads[n];
    int ids[n];

    sem_init (&eat,0,n-1);

    for (int i = 0; i < n; i++)
    {   
        sem_init(&forks[i],0,1);
        /* code */
    }

    for(int i=0;i<n;i++){
        ids[i]=i;
        pthread_create(&threads[i],NULL,philospher,&ids[i]);
    }

    for(int i=0;i<n;i++){
        
        pthread_join(threads[i],NULL);
    }

    
return 0;
}
