#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#define BUF_LENGTH 256
int main(int argc, char** argv) {
    char* src = argv[1];
    char* dst = argv[2];

    //Open file to be read
    int srcFile = open(src, O_RDONLY);
    //Open file to write on
    int dstFile = open(dst, (O_WRONLY | O_TRUNC | O_CREAT | O_SYNC), (S_IRUSR | S_IXUSR));

    char buf[BUF_LENGTH];
    int nBytes = read(srcFile, buf, BUF_LENGTH);
    write(dstFile, buf, nBytes);
   
    close(srcFile);
    close(dstFile);
    exit(0);  // zero é geralmente indicativo de "sucesso"
}

