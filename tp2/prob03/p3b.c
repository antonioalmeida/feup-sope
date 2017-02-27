#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUF_LENGTH 256
int main(int argc, char** argv) {
    char* src = argv[1];
    int dstFile;
    if(argc == 3) {
        dstFile = open(argv[2], (O_WRONLY | O_CREAT | O_SYNC), (S_IRUSR | S_IWUSR | S_IXUSR));
        dup2(dstFile, STDOUT_FILENO);
    }

    //Open file to be read
    int srcFile = open(src, O_RDONLY);

    char buf[BUF_LENGTH];
    int nBytes = read(srcFile, buf, BUF_LENGTH);
    write(STDOUT_FILENO, buf, nBytes);
   
    close(srcFile);
    exit(0);  // zero é geralmente indicativo de "sucesso"
}

