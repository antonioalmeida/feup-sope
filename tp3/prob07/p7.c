// PROGRAMA p7.c
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

/* O programa substitui o seu código por outro programa que, no caso, representa a compilação de um programa cujo nome é especificado
 * por um argumento na linha de comandos
 */

int main(int argc, char *argv[]) {
    char prog[20];
    sprintf(prog,"%s.c",argv[1]);
    execlp("gcc","gcc",prog,"-Wall","-o",argv[1],NULL);
    printf("Compilation failed");
    exit(-1);
}