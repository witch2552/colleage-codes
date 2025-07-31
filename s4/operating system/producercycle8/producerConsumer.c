#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;
pthread_mutex_t mutex;
sem_t full, empty;
void *producer(void *arg)
{
    int item = 0;
    while (1)
    {
        item++;
        sem_wait(&empty);
        pthread_mutex_lock(&mutex);
        buffer[count] = item;
        printf("Producer produced: %d\n", item);
        count++;
        pthread_mutex_unlock(&mutex);
        sem_post(&full);
        sleep(1);
    }
}
void *consumer(void *arg)
{
    while (1)
    {
        sem_wait(&full);
        pthread_mutex_lock(&mutex);
        count--;
        int item = buffer[count];
        printf("Consumer consumed: %d\n", item);
        pthread_mutex_unlock(&mutex);
        sem_post(&empty);
        sleep(2);
    }
}
int main()
{
    pthread_t prod, cons;
    pthread_mutex_init(&mutex, NULL);
    sem_init(&full, 0, 0);
    sem_init(&empty, 0, BUFFER_SIZE);
    pthread_create(&prod, NULL, producer, NULL);
    pthread_create(&cons, NULL, consumer, NULL);
    pthread_join(prod, NULL);
    pthread_join(cons, NULL);
    pthread_mutex_destroy(&mutex);
    sem_destroy(&full);
    sem_destroy(&empty);                                                        
    return 0;
}
