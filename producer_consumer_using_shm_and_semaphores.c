#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <semaphore.h>
#include <pthread.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 15
#define NUM_CONSUMERS 10


typedef struct {
    int buffer[BUFFER_SIZE];
    int in;
    int out;
    sem_t empty;
    sem_t full;
    sem_t mutex;
} SharedMemory;

void *producer(void *arg) {
    SharedMemory *sharedMemory = (SharedMemory *)arg;

    {
        sem_wait(&(sharedMemory->empty));
        sem_wait(&(sharedMemory->mutex));

        int item = rand() % 100;
        sharedMemory->buffer[sharedMemory->in] = item;
        printf("Produced: %d\n", item);
        sharedMemory->in = (sharedMemory->in + 1) % BUFFER_SIZE;

        sem_post(&(sharedMemory->mutex));
        sem_post(&(sharedMemory->full));

        usleep(rand() % 1000000); // Simulate production time
    }

    return NULL;
}

void *consumer(void *arg) {
    SharedMemory *sharedMemory = (SharedMemory *)arg;

    {
        sem_wait(&(sharedMemory->full));
        sem_wait(&(sharedMemory->mutex));

        int item = sharedMemory->buffer[sharedMemory->out];
        printf("Consumed: %d\n", item);
        sharedMemory->out = (sharedMemory->out + 1) % BUFFER_SIZE;

        sem_post(&(sharedMemory->mutex));
        sem_post(&(sharedMemory->empty));

        usleep(rand() % 1500000); // Simulate consumption time
    }

    return NULL;
}

int main() {
    int shmid;
    SharedMemory *sharedMemory;

    shmid = shmget(IPC_PRIVATE, sizeof(SharedMemory), IPC_CREAT | 0666);
    sharedMemory = (SharedMemory *)shmat(shmid, NULL, 0);

    sharedMemory->in = 0;
    sharedMemory->out = 0;

    sem_init(&(sharedMemory->empty), 1, BUFFER_SIZE);
    sem_init(&(sharedMemory->full), 1, 0);
    sem_init(&(sharedMemory->mutex), 1, 1);

    pthread_t producer_threads[NUM_PRODUCERS];
    pthread_t consumer_threads[NUM_CONSUMERS];

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_create(&producer_threads[i], NULL, producer, NULL;
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_create(&consumer_threads[i], NULL, consumer, NULL);
    }

    for (int i = 0; i < NUM_PRODUCERS; i++) {
        pthread_join(producer_threads[i], NULL);
    }

    for (int i = 0; i < NUM_CONSUMERS; i++) {
        pthread_join(consumer_threads[i], NULL);
    }

    sem_destroy(&(sharedMemory->empty));
    sem_destroy(&(sharedMemory->full));
    sem_destroy(&(sharedMemory->mutex));

    shmdt(sharedMemory);
    shmctl(shmid, IPC_RMID, NULL);

    return 0;
}
