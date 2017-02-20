#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256
int main(int argc, char** argv) {
    printf("Write a command to be split into its tokens : ");
    char str[MAX_LENGTH];
    fgets(str, MAX_LENGTH, stdin);

    char* token;
    token = strtok(str," ");
    printf("Tokens\n\n");
    while(token != NULL) {
        printf("%s\n", token);
        token = strtok(NULL," ");
    }
    exit(0);
} 
