     #include <pthread.h>
     #include <stdio.h>
     #include <unistd.h>
     #include <stdlib.h>
     #define NUM_THREADS 10

void *PrintHello(void *threadnum) {
        sleep(1);
        pthread_t selfTid = pthread_self();
        printf("Hello from thread no. %d with TID %d\n", *((int *) threadnum), (int) selfTid);
        pthread_exit(threadnum);
}
int main() {
        pthread_t threads[NUM_THREADS];
        int t;
        for(t=0; t < NUM_THREADS; t++) {
                printf("Creating thread %d\n", t);
                pthread_create(&threads[t], NULL, PrintHello, (void *)&t);
                pthread_join(threads[t], NULL);
        }
        pthread_exit(0);
}
