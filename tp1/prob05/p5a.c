#include <stdio.h>
#include <unistd.h>
extern char **environ;

int main(int argc, char** argv) {
    int i = 0;
    while(environ[i++] != 0) { //Last element of environ is a NULL pointer
        printf("%s \n", environ[i]);
    }
}

