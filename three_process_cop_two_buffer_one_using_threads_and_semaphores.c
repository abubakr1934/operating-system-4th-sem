#include <pthread.h>
#include <semaphore.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int *a; // for shared memory

sem_t sem1, sem2, sem3; // for three different processes

void *processA(void *arg) {
    int *a = (int *)arg;
    sem_wait(&sem1);
    int j = rand() % 100;
    *a = j;
    printf("Process one is writing content into buffer 1 and data written is %d\n", *a);
    sem_post(&sem1);
    sem_post(&sem2);
    return NULL;
}

void *processB(void *arg) {
    int *a = (int *)arg;
    sem_wait(&sem2);
    printf("Process 2 is copying data from buffer 1 to buffer 2\n");
    int copy = *a;
    printf("Contents being copied are %d\n", copy);
    *a = copy;
    sem_post(&sem2);
    sem_post(&sem3);
    return NULL;
}

void *processC(void *arg) {
    sem_wait(&sem3);
    printf("Contents are being printed from buffer 2: %d\n", *a);
    sem_post(&sem3);
    return NULL;
}

int main() {
    key_t key;
    key = 5678;
    pthread_t TA[3], TB[3], TC[3];
    int shmid = shmget(key, sizeof(int), IPC_CREAT | 0666);
    a = (int *)shmat(shmid, NULL, 0);
    sem_init(&sem1, 0, 1);
    sem_init(&sem2, 0, 0);
    sem_init(&sem3, 0, 0);

    for (int i = 0; i < 3; i++) {
        pthread_create(&TA[i], NULL, &processA, a);
    }
    for (int i = 0; i < 3; i++) {
        pthread_create(&TB[i], NULL, &processB, a);
    }
    for (int i = 0; i < 3; i++) {
        pthread_create(&TC[i], NULL, &processC, a);
    }

    for (int i = 0; i < 3; i++) {
        pthread_join(TA[i], NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(TB[i], NULL);
    }
    for (int i = 0; i < 3; i++) {
        pthread_join(TC[i], NULL);
    }

    shmdt(a);
    shmctl(shmid, IPC_RMID, NULL);
    return 0;
}
