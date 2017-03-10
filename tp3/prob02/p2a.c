#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
int main(void) {
    write(STDOUT_FILENO,"1",1);
    if(fork() > 0) {
        write(STDOUT_FILENO,"2",1);
        write(STDOUT_FILENO,"3",1);
    } else {
        write(STDOUT_FILENO,"4",1);
        write(STDOUT_FILENO,"5",1);
    }
    write(STDOUT_FILENO,"\n",1);
    return 0;
}