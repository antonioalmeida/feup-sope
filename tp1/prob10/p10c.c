#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGTH 256
int main(int argc, char** argv) {
    printf("Write a command to be split into its tokens : ");
    char str[MAX_LENGTH];
    fgets(str, MAX_LENGTH, stdin);

    //strtok changes argument, so creating a new string to hold original input
    char original[MAX_LENGTH];
    strcpy(original, str);

    char* token;
    char* test;
    char* delim;
    test = strtok(str,"|");
    test = strtok(NULL, "|");

    if(test == NULL) 
        delim = ";";
    else 
        delim = "|";

    printf("delim = %s\n", delim);
    token = strtok(original,delim);
    printf("Tokens\n\n");

    int i = 0;
    char* arr[MAX_LENGTH];
    while(token != NULL) {
        arr[i++] = token;
        token = strtok(NULL,delim);
    }
    
    for(int j = 0; j < i; j++) 
        printf("%s\n", arr[j]);

    exit(0);
} 
