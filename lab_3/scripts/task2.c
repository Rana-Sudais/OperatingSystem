#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main() {
    pid_t pid = fork();   // create a new process

    if (pid < 0) {
        perror("fork failed");    // error in creating process
        return 1;
    }

    if (pid == 0) {
        // 🧒 Child process: execute "date"
        execlp("date", "date", NULL);
        perror("execlp failed");  // runs only if execlp fails
        exit(1);
    } 
    else {
        // 👨 Parent process: wait for child to finish
        wait(NULL);
        printf("Child finished\n");
    }

    return 0;
}