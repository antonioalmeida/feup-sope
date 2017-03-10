#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    printf("1\n");
    if(fork() > 0) {
        printf("2");
        printf("3");
    } else {
        printf("4");
        printf("5");
    }
    printf("\n");
    return 0;
}