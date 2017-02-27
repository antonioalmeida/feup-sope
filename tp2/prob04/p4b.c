#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#define BUF_LENGTH 256
#define MAX_NAME_LENGTH 50
#define MAX_STUDENTS 5
#define DST_FILE "output.dat"
#define OK 0

struct Student {
    char* name;
    int grade;
};

int main(int argc, char** argv) {

    //Open file in binary mode
    FILE* dstFile = fopen(DST_FILE, "wb");
    if(dstFile == NULL) {
        perror(dstFile);
        exit(-1);
    }
    int DST_FILENO = fileno(dstFile);

    write(STDOUT_FILENO, "Starting student's names registration.\n", 39);
    char* number = (char*)malloc(BUF_LENGTH);
    int counter = 0;

    do {
        struct Student elem;
        elem.name = (char*)malloc(MAX_NAME_LENGTH);
        write(STDOUT_FILENO, "Insert a student's name : ", 26);
        read(STDIN_FILENO, elem.name, BUF_LENGTH);

        write(STDOUT_FILENO, "Insert a student's grade : ", 27);
        read(STDIN_FILENO, number, BUF_LENGTH);

        elem.grade = (int)strtol(number, NULL, 10); 
        write(DST_FILENO, &elem, sizeof(struct Student));
        counter++;
    } while(counter < MAX_STUDENTS); 

    fclose(dstFile);

    printf("\nPrinting the file...\n\n");

    //Print part by @cyrilico
    FILE* SRC_FILE;
    if((SRC_FILE = fopen(DST_FILE,"rb")) == NULL)
        exit(-1);
    struct Student s2;
    int i = 0;
    for(i; i < counter; i++){
        fread(&s2, sizeof(struct Student), 1, SRC_FILE);
        printf("%s %d\n", s2.name, s2.grade);
    }
    exit(0);
}


