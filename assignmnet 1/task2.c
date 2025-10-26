#include <stdio.h>
#include <pthread.h>
#include <string.h>

void* greeting(void* arg) {
    char* name = (char*)arg;
    printf("Thread says: Hello, %s! Welcome to the world of threads.\n", name);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    char name[50];

    printf("Enter your name: ");
    scanf("%s", name);

    printf("Main thread: Waiting for greeting…\n");
    pthread_create(&tid, NULL, greeting, name);
    pthread_join(tid, NULL);
    printf("Main thread: Greeting completed.\n");
    return 0;
}