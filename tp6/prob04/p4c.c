     #include <pthread.h>
     #include <stdio.h>
     #include <unistd.h>
     #include <stdlib.h>
     #define NUM_THREADS 10

void *PrintHello(void *threadnum) {
        sleep(1);
        pthread_t selfTid = pthread_self();
        printf("Hello from thread no. %d with TID %d\n", *((int *) threadnum), (int) selfTid);

        return threadnum;
}

int main() {
        pthread_t threads[NUM_THREADS];
        int t;
        void* returnValue = NULL;
        for(t=0; t < NUM_THREADS; t++) {
                pthread_create(&threads[t], NULL, PrintHello, (void *)&t);
                pthread_join(threads[t], &returnValue);
                printf("Thread no. %d returned %d\n", t, *((int *) returnValue));
        }
        pthread_exit(0);
}
