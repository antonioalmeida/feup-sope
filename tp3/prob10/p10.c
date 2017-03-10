// PROGRAMA p8.c
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>

#define PERMISSIONS 0777

int main(int argc, char *argv[], char *envp[]) {
    pid_t pid;
    if (argc != 2 && argc != 3) {
        printf("usage: %s dirname [output file]\n",argv[0]);
        exit(1);
    }

    if(argc == 3) {
        int DST_FILENO = open(argv[2], (O_CREAT | O_TRUNC | O_WRONLY), PERMISSIONS);
        if(DST_FILENO == -1)
            perror("Error ");
        dup2(DST_FILENO, STDOUT_FILENO);
    }

    pid=fork();
    if (pid > 0)
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);
    else if (pid == 0) {
        execlp("ls", "ls" , "-laR", argv[1], NULL);
        printf("Command not executed !\n");
        exit(1);
    }
    exit(0);
}