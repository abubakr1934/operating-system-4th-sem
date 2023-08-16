#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include<unistd.h>

#define BUFFER_SIZE 5
#define NUM_PRODUCERS 10
#define NUM_CONSUMERS 10

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t empty, full, mutex;

void *producer(void *arg) {
  int item = 1;

  while (1) {
    sem_wait(&empty);
    sem_wait(&mutex);

    // Produce item and add it to the buffer
    buffer[in] = item;
    printf("Produced: %d\n", item);
    in = (in + 1) % BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&full);

    item++;
    sleep(1000000); // Simulate production time
  }

  return NULL;
}

void *consumer(void *arg) {
  while (1) {
    sem_wait(&full);
    sem_wait(&mutex);

    // Consume item from the buffer
    int item = buffer[out];
    printf("Consumed: %d\n", item);
    out = (out + 1) % BUFFER_SIZE;

    sem_post(&mutex);
    sem_post(&empty);

    usleep(1500000); // Simulate consumption time
  }

  return NULL;
}

int main() {
  sem_init(&empty, 0, BUFFER_SIZE);
  sem_init(&full, 0, 0);
  sem_init(&mutex, 0, 1);

  pthread_t producer_threads[NUM_PRODUCERS];
  pthread_t consumer_threads[NUM_CONSUMERS];

  for (int i = 0; i < NUM_PRODUCERS; i++) {
    pthread_create(&producer_threads[i], NULL, producer, NULL);
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

  sem_destroy(&empty);
  sem_destroy(&full);
  sem_destroy(&mutex);

  return 0;
}
