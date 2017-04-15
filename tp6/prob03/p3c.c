// PROGRAMA p03.c
     #include <pthread.h>
     #include <stdio.h>
     #include <stdlib.h>
     #define NUM_THREADS 10

// A função de thread nunca é executada
// Não sei porquê, mas tem algo a ver com o facto do thread da função main não estar a ser terminado (no shit sherlock)

void *PrintHello(void *threadnum) {
        printf("Hello from thread no. %d!\n", *(int *) threadnum);
        pthread_exit(NULL);
}
int main() {
        pthread_t threads[NUM_THREADS];
        int t;
        for(t=0; t< NUM_THREADS; t++) {
                printf("Creating thread %d\n", t);
                pthread_create(&threads[t], NULL, PrintHello, (void *)&t);
        }
        exit(0);
}
