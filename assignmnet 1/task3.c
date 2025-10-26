#include <stdio.h>
#include <pthread.h>

void* number_info(void* arg) {
    int num = *((int*)arg);
    printf("Thread: Number = %d, Square = %d, Cube = %d\n", num, num*num, num*num*num);
    pthread_exit(NULL);
}

int main() {
    pthread_t tid;
    int num;

    printf("Enter an integer: ");
    scanf("%d", &num);

    pthread_create(&tid, NULL, number_info, &num);
    pthread_join(tid, NULL);
    printf("Main thread: Work completed.\n");
    return 0;
}