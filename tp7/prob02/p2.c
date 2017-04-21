#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#define STDERR 2
#define NCHARS 50000

int N = NCHARS,
    initialN = NCHARS,
    thread1N = 1,
    thread2N = 2;

pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;     /* mutex para s.c */

void * thrfunc(void * arg) {
        fprintf(stderr, "Starting thread %s\n", (char *) arg);
        int* result = malloc(sizeof(int));
        while(N-- > 0) {
                pthread_mutex_lock(&mut);
                write(STDERR,"1",1);
                (*result)++;
                pthread_mutex_unlock(&mut);
        }

        return result;
}

int main() {
        pthread_t ta, tb;

        pthread_create(&ta, NULL, thrfunc, &thread1N);
        pthread_create(&tb, NULL, thrfunc, &thread2N);

        void* returnThread1;
        void* returnThread2;

        pthread_join(ta, &returnThread1);
        pthread_join(tb, &returnThread2);

        printf("\nThread 1 wrote : %d characters\n", *((int *)returnThread1));
        printf("Thread 2 wrote : %d characters\n", *((int *)returnThread2));

        int totalChars = *((int *)returnThread1) + *((int *)returnThread2);
        printf("Total characters written : %d, expected %d\n", totalChars, initialN);

        pthread_mutex_destroy(&mut);
        return 0;
}
