// PROGRAMA p5a.c
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
    int fd;
    char *text1="AAAAA";
    char *text2="BBBBB";

    fd = open("f1.txt",O_CREAT|O_EXCL|O_TRUNC|O_WRONLY|O_SYNC,0600);

    if(fd == -1) {
        perror("Error ");
        return -1;
    }

    write(STDOUT_FILENO, "Writing AAAAA to f1.txt. 'y' to confirm, anything else to cancel : ", 67);
    char c = getchar();
    
    if(c == 'y')
        write(fd,text1,5);

    //clear input buffer
    fseek(stdin, 0, SEEK_END);

    write(STDOUT_FILENO, "Writing BBBBB to f1.txt. 'y' to confirm, anything else to cancel : ", 67);
    char c2 = getchar();
    if(c2 == 'y')
        write(fd,text2,5);

    close(fd);
    return 0;
}

