#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>

#define N 5

int buffer[N], in = 0, out = 0, item = 0, n;
sem_t empty, full, mutex;

void* producer(void* arg) {
    for (int i = 0; i < n; i++) {
        sem_wait(&empty);
        sem_wait(&mutex);

        buffer[in] = item;
        printf("Produced: %d at buffer[%d]\n", item, in);
        in = (in + 1) % N;
        item++;

        sem_post(&mutex);
        sem_post(&full);
    }
    return NULL;
}

void* consumer(void* arg) {
    for (int i = 0; i < n; i++) {
        sem_wait(&full);
        sem_wait(&mutex);

        int val = buffer[out];
        printf("Consumed: %d from buffer[%d]\n", val, out);
        out = (out + 1) % N;

        sem_post(&mutex);
        sem_post(&empty);
    }
    return NULL;
}

int main() {
    pthread_t p, c;

    printf("Enter number of items: ");
    scanf("%d", &n);

    sem_init(&empty, 0, N);
    sem_init(&full, 0, 0);
    sem_init(&mutex, 0, 1);

    pthread_create(&p, NULL, producer, NULL);
    pthread_create(&c, NULL, consumer, NULL);

    pthread_join(p, NULL);
    pthread_join(c, NULL);

    return 0;
}
