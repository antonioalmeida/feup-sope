#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#define BUF_LENGTH 256
#define DST_FILE "output.txt"

int main(int argc, char** argv) {
    int DST_FILENO = open(DST_FILE, (O_WRONLY | O_CREAT | O_SYNC | O_EXCL), (S_IRUSR | S_IWUSR | S_IXUSR));
    if(DST_FILENO == -1) {
        perror("Error opening file ");
        exit(-1);
    }

    write(STDOUT_FILENO, "Starting student's names registration.\nPress CTRL+C to finish input.\n", 71);
    char* input = (char*)malloc(BUF_LENGTH);
    char* number = (char*)malloc(BUF_LENGTH);
    int nBytes;

    do {
        write(STDOUT_FILENO, "Insert a student's name : ", 26);
        nBytes = read(STDIN_FILENO, input, BUF_LENGTH);
        write(DST_FILENO, input, nBytes);
        write(STDOUT_FILENO, "Insert a student's grade : ", 27);
        nBytes = read(STDIN_FILENO, number, BUF_LENGTH);
        write(DST_FILENO, ' ', 1);
        write(DST_FILENO, number, nBytes);
    } while(1); //CTRL+C to terminate

    close(DST_FILENO);
    exit(0);  // zero é geralmente indicativo de "sucesso"
}


