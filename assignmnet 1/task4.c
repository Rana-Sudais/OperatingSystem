#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* factorial(void* arg) {
    int n = *((int*)arg);
    long long* result = malloc(sizeof(long long));
    *result = 1;
    for (int i = 1; i <= n; i++)
        *result *= i;
    pthread_exit(result);
}

int main() {
    pthread_t tid;
    int n;
    long long* result;

    printf("Enter a number: ");
    scanf("%d", &n);

    pthread_create(&tid, NULL, factorial, &n);
    pthread_join(tid, (void**)&result);

    printf("Factorial of %d = %lld\n", n, *result);
    free(result);
    return 0;
}