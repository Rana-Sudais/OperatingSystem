#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();   // create a new child process

    if (pid < 0) {
        // fork failed
        perror("fork failed");
        return 1;
    }

    if (pid == 0) {
        // 🧒 Child process: replace itself with the "top" command
        printf("Child Process: running 'top'...\n");
        execlp("top", "top", NULL);

        // if execlp fails, this line runs
        perror("execlp failed");
        exit(1);
    } 
    else {
        // 👨 Parent process: wait for the child to finish
        printf("Parent Process: spawned child with PID %d\n", pid);
        wait(NULL);     // parent waits until child finishes
        printf("Child finished — parent exiting now.\n");
    }

    return 0;
}