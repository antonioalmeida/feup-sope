#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void handler0() {
    printf("Executing handler 0\n");
}

void handler1() {
    printf("Executing handler 1\n");
}

void handler2() {
    printf("Executing handler 2\n");
}

 int main(int argc, char** argv) {
    if(argc != 2) {
        printf("Wrong number of arguments. Usage : ./p7a int[0,2]\n");
        return -1;
    }

     const char* arg = argv[1];
     if(strncmp(arg,"0",1) == 0)
           atexit(handler0);
     if(strncmp(arg,"1",1) == 0)
           atexit(handler1);
     if(strncmp(arg, "2",1) == 0)
           atexit(handler2);
   
     printf("Main done!\n");
 }
