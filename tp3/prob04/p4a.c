#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>

int main(void) {
    pid_t pid = fork();

    if (pid == -1) {
        perror("Fork ERROR ");
        exit(1);
    }

    if (pid != 0)
        printf("Hello ");
    else
        printf("World!\n");

    exit(0);
}