#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(void) {

    write(STDOUT_FILENO, "Hello ", 6);

    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork ERROR ");
        exit(1);
    }

    if (pid == 0) {
        write(STDOUT_FILENO, "my ", 3);
        int pid2 = fork();

        if(pid2 == 0) {
            write(STDOUT_FILENO, "friends!\n", 9);
        }
    }

    exit(0);
}