// PROGRAMA p01.c
     #include <stdio.h>
     #include <unistd.h>
     #include <pthread.h>
     #define STDERR 2
     #define NUMITER 10000

void * thrfunc(void * arg) {
        int i;
        fprintf(stderr, "Starting thread %d\n", *((int *) arg));
        for (i = 1; i <= NUMITER; i++) write(STDERR, (int *) arg, 1); //This isn't working
        return NULL;
}
int main() {
        pthread_t ta, tb;
        int arg = 1;
        pthread_create(&ta, NULL, thrfunc, &arg);
        arg = 2;
        pthread_create(&tb, NULL, thrfunc, &arg);
        pthread_join(ta, NULL);
        pthread_join(tb, NULL);
        return 0;
}
