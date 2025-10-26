#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <time.h>

void* display_info(void* arg) {
    int thread_num = *((int*)arg);
    printf("Thread %d started. Thread ID: %lu\n", thread_num, pthread_self());
    int sleep_time = (rand() % 3) + 1;
    sleep(sleep_time);
    printf("Thread %d completed after %d seconds.\n", thread_num, sleep_time);
    pthread_exit(NULL);
}

int main() {
    pthread_t threads[5];
    int thread_nums[5];
    srand(time(NULL));

    for (int i = 0; i < 5; i++) {
        thread_nums[i] = i + 1;
        pthread_create(&threads[i], NULL, display_info, &thread_nums[i]);
    }

    for (int i = 0; i < 5; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished execution.\n");
    return 0;
}