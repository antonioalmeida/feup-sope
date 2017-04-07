// PROGRAMA p01.c
     #include <stdio.h>
     #include <unistd.h>
     #include <pthread.h>
     #define STDERR 2
     #define NUMITER 10000

//Quando é utilizada a mesma variável em ambos os threads, o thread 1 utiliza o valor do argumento depois da atualização do valor, ou seja,
//imprime 2 em vez de 1

void * thrfunc(void * arg) {
        int i;
        fprintf(stderr, "Starting thread %s\n", (char *) arg);
        for (i = 1; i <= NUMITER; i++) write(STDERR,arg,1);
        return NULL;
}
int main() {
        pthread_t ta, tb;
        char arg = '1';
        pthread_create(&ta, NULL, thrfunc, &argA);
        arg = '2';
        pthread_create(&tb, NULL, thrfunc, &arg);
        pthread_join(ta, NULL);
        pthread_join(tb, NULL);
        return 0;
}
