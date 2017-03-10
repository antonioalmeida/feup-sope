#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_LENGTH 256

int main(int argc, char *argv[], char *envp[]) {
    pid_t pid;
    int childStatus;

    if (argc != 2) {
        printf("usage: %s dirname\n", argv[0]);
        exit(1);
    }

    pid=fork();
    if (pid > 0) {
        printf("My child is going to execute command \"ls -laR %s\"\n", argv[1]);

        waitpid(pid, &childStatus, WUNTRACED); //Wait for child
        printf("My child returned %i\n", WEXITSTATUS(childStatus));

        if(WIFEXITED(childStatus)) //Child finished normally
            printf("My child finished normally\n");
        if(WIFSIGNALED(childStatus)) //Child finished abnormally
            printf("My child terminated abnormally with signal %i\n", WTERMSIG(childStatus));

        exit(0);
    }
    else if (pid == 0) {
        execlp("ls", "ls" , "-laR", argv[1], NULL);
    }

    exit(0);
}