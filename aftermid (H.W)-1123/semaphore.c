#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define BUFFER_SIZE 5
#define ITEMS_PER_THREAD 3

int buffer[BUFFER_SIZE];
int in = 0, out = 0;

sem_t emptySlots;      // Number of empty buffer slots
sem_t fullSlots;       // Number of filled buffer slots
pthread_mutex_t lock;

// ---------------- PRODUCER ----------------
void* producer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < ITEMS_PER_THREAD; i++) {
        int item = id * 100 + i;

        sem_wait(&emptySlots);          // Wait for empty space
        pthread_mutex_lock(&lock);      // Lock buffer

        buffer[in] = item;
        printf("Producer %d produced %d at index %d\n", id, item, in);
        in = (in + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&lock);    // Unlock buffer
        sem_post(&fullSlots);           // Signal item available

        sleep(1);
    }
    return NULL;
}

// ---------------- CONSUMER ----------------
void* consumer(void* arg) {
    int id = *(int*)arg;

    for (int i = 0; i < ITEMS_PER_THREAD; i++) {
        sem_wait(&fullSlots);            // Wait for item
        pthread_mutex_lock(&lock);       // Lock buffer

        int item = buffer[out];
        printf("Consumer %d consumed %d from index %d\n", id, item, out);
        out = (out + 1) % BUFFER_SIZE;

        pthread_mutex_unlock(&lock);     // Unlock buffer
        sem_post(&emptySlots);           // Signal empty slot

        sleep(2);
    }
    return NULL;
}

int main() {
    pthread_t producers[2], consumers[2];
    int ids[2] = {1, 2};

    sem_init(&emptySlots, 0, BUFFER_SIZE);
    sem_init(&fullSlots, 0, 0);
    pthread_mutex_init(&lock, NULL);

    for (int i = 0; i < 2; i++) {
        pthread_create(&producers[i], NULL, producer, &ids[i]);
        pthread_create(&consumers[i], NULL, consumer, &ids[i]);
    }

    for (int i = 0; i < 2; i++) {
        pthread_join(producers[i], NULL);
        pthread_join(consumers[i], NULL);
    }

    sem_destroy(&emptySlots);
    sem_destroy(&fullSlots);
    pthread_mutex_destroy(&lock);

    return 0;
}
