#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

int main(int argc, char *argv[]) {
        pid_t pid, pid2;
        int fd1[2], // grep <==> sort
            fd2[2]; // ls -laR <==> grep

        if (argc != 3) {
                printf("usage: %s filename type\n", argv[0]);
                exit(1);
        }

        pipe(fd1);
        pid = fork();
        switch(pid) {
        case -1:
                printf("fork error\n");
                exit(1);
        case 0:     //  child of sort -> either ls -laR or grep
                pipe(fd2);

                pid2 = fork();
                switch(pid2) {
                case -1:
                        printf("fork error\n");
                        exit(1);
                case 0:     // child of child -> ls laR
                        if(fd2[WRITE] != STDOUT_FILENO) {
                                dup2(fd2[WRITE], STDOUT_FILENO);
                                close(fd2[WRITE]);
                        }
                        close(fd2[READ]);
                        execlp("ls", "ls", "-laR", argv[1], NULL);
                        exit(1);

                default: // grep
                        if(fd2[READ] != STDIN_FILENO) {
                                dup2(fd2[READ], STDIN_FILENO);
                                close(fd2[READ]);
                        }
                        close(fd2[WRITE]);
                        if(fd1[WRITE] != STDOUT_FILENO) {
                                dup2(fd1[WRITE], STDOUT_FILENO);
                                close(fd1[WRITE]);
                        }
                        close(fd1[READ]);
                        execlp("grep", "grep", argv[2], NULL);
                        exit(2);
                }

                exit(3);
        default: // sort
                close(fd1[WRITE]);
                close(fd2[READ]);
                close(fd2[WRITE]);
                if (fd1[READ] != STDIN_FILENO) {
                        dup2(fd1[READ], STDIN_FILENO);
                        close(fd1[READ]);
                }
                execlp("sort", "sort", NULL);
                exit(3);
        }

        exit(0);
}
