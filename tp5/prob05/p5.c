#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_LENGTH 256
#define READ 0
#define WRITE 1


char* get_first_arg(char* cmd) {
        char* copy = (char*) malloc(MAX_LENGTH);
        strcpy(copy, cmd);
        char* token = strtok(copy, " ");

        if(token == NULL)
                return cmd;

        return token;
}

char** get_argv(char* cmd) {
        char copy[MAX_LENGTH];
        strcpy(copy, cmd);
        char* token;

        int i = 0;
        char** arr = (char **) malloc(MAX_LENGTH);
        token = strtok(copy, " ");
        while(token != NULL) {
                arr[i++] = token;
                token = strtok(NULL, " ");
        }
        arr[i] = NULL;

        return arr;
}

int spawn_proc(int in, int out, char* cmd) {
        pid_t pid;

        if ((pid = fork ()) == 0) {
                if (in != STDIN_FILENO) {
                        dup2(in, STDIN_FILENO);
                        close(in);
                }
                if (out != STDOUT_FILENO) {
                        dup2(out, STDOUT_FILENO);
                        close(out);
                }
                int r_value = execvp(get_first_arg(cmd), get_argv(cmd));
                if(r_value != 0) {
                        fprintf(stderr, "Error with execvp %s ", cmd);
                        perror("");
                }
                return r_value;
        }
        return pid;
}

int fork_pipes (int n, char** cmds) {
        int i;
        int in, fd[2];

        /* The first process should get its input from the original file descriptor STDIN_FILENO.  */
        in = STDIN_FILENO;

        /* Note the loop bound, we spawn here all, but the last stage of the pipeline.  */
        for (i = 0; i < n - 1; ++i) {
                pipe (fd);

                /* f[1] is the write end of the pipe, we carry `in` from the prev iteration.  */
                spawn_proc(in, fd[WRITE], cmds[i]);

                /* No need for the write end of the pipe, the child will write here.  */
                close(fd[WRITE]);

                /* Keep the read end of the pipe, the next child will read from there.  */
                in = fd[READ];
        }

        /* Last stage of the pipeline - set stdin be the read end of the previous pipe
           and output to the original file descriptor 1. */
        if (in != STDIN_FILENO)
                dup2(in, 0);

        /* Execute the last stage with the current process. */
        int r_value = execvp(get_first_arg(cmds[i]), get_argv(cmds[i]));
        if(r_value != 0) {
                fprintf(stderr, "Error with execvp %s ", cmds[i]);
                perror("");
        }
        printf("%d", r_value);
        return r_value;
}


int main(int argc, char** argv) {
        printf("Write a command to be split into its tokens : ");
        char str[MAX_LENGTH];
        fgets(str, MAX_LENGTH, stdin);

        char* token;
        char* delim = "|";

        printf("delim = %s\n", delim);
        printf("Tokens\n\n");

        int i = 0;
        char* arr[MAX_LENGTH];
        token = strtok(str,delim);
        while(token != NULL) {
                arr[i++] = token;
                token = strtok(NULL,delim);
        }
        arr[i-1][strlen(arr[i-1])-1] = 0;

        int j;
        for(j = 0; j < i; j++)
                printf("%s\n", arr[j]);
        printf("\n");

        return fork_pipes(i, arr);

        exit(0);
}
