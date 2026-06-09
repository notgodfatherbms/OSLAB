#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>

int N;
sem_t *forks, mutex;

void* philosopher(void* num) {
    int i = *(int*)num;

    for (int k = 0; k < 2; k++) {
        printf("Philosopher %d is thinking.\n", i);

        sem_wait(&mutex);
        sem_wait(&forks[i]);
        printf("Philosopher %d picked up left fork %d.\n", i, i);

        sem_wait(&forks[(i+1)%N]);
        printf("Philosopher %d picked up right fork %d.\n", i, (i+1)%N);
        sem_post(&mutex);

        printf("Philosopher %d is eating.\n", i);

        sem_post(&forks[i]);
        sem_post(&forks[(i+1)%N]);

        printf("Philosopher %d put down forks %d and %d.\n", i, i, (i+1)%N);
    }
    return NULL;
}

int main() {
    printf("Enter number of philosophers: ");
    scanf("%d", &N);

    pthread_t p[N];
    int id[N];

    forks = (sem_t*)malloc(N * sizeof(sem_t));

    sem_init(&mutex, 0, 1);
    for (int i = 0; i < N; i++)
        sem_init(&forks[i], 0, 1);

    for (int i = 0; i < N; i++) {
        id[i] = i;
        pthread_create(&p[i], NULL, philosopher, &id[i]);
    }

    for (int i = 0; i < N; i++)
        pthread_join(p[i], NULL);

    return 0;
}
