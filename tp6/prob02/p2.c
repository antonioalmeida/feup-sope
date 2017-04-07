// PROGRAMA p01.c
     #include <stdio.h>
     #include <unistd.h>
     #include <pthread.h>
     #define STDERR 2
     #define NUMITER 10000

int N = 50000,
    initialN = 50000,
    thread1N = 1,
    thread2N = 2;

void * thrfunc(void * arg) {
        fprintf(stderr, "Starting thread %s\n", (char *) arg);
        *((int *)arg) = (int) 0;
        while(N-- > 0) {
                write(STDERR,"1",1);
                *((int *)arg) = *((int *) arg) +1;
        }
}

int main() {
        pthread_t ta, tb;

        pthread_create(&ta, NULL, thrfunc, &thread1N);
        pthread_create(&tb, NULL, thrfunc, &thread2N);
        pthread_join(ta, NULL);
        pthread_join(tb, NULL);

        printf("\nThread 1 wrote : %d characters\n", thread1N);
        printf("Thread 2 wrote : %d characters\n", thread2N);
        printf("Total characters written : %d, expected %d\n", (thread1N+thread2N), initialN);
        return 0;
}
