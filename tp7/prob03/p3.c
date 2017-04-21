#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define MAXPOS 10000000 /* nr. max de posições */
#define MAXTHRS 100 /* nr. max de threads */
#define min(a, b) (a)<(b) ? (a) : (b)

//O programa utiliza vários threads para preencher um array comum (em cada posição é colocado o seu índice)
//No final é corrido um último thread para verificar se ocorreram erros no preenchimento do array

int npos;
pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER; /* mutex para s.c */
pthread_cond_t cvar=PTHREAD_COND_INITIALIZER; /* variavel de condicao */
int buf[MAXPOS], pos=0, val=0; /* variáveis partilhadas */
void *fill(void *);
void *verify(void *);

int main(int argc, char *argv[]) {
        int k, nthr, count[MAXTHRS]; /* array para contagens */
        pthread_t tidf[MAXTHRS], tidv; /* tid’s dos threads */

        if (argc != 3) {
                printf("Usage: fillver <nr_pos> <nr_thrs>\n");
                return 1;
        }

        npos = min(atoi(argv[1]), MAXPOS); /* nr. efectivo de posições */
        nthr = min(atoi(argv[2]), MAXTHRS);        /* nr. efectivo de threads */
        for (k=0; k<nthr; k++) {
                count[k] = 0; /* criação dos threads fill() */
                pthread_create(&tidf[k], NULL, fill, &count[k]);
        }
        pthread_create(&tidv, NULL, verify, NULL);

        for (k=0; k<nthr; k++) {
                pthread_join(tidf[k], NULL); /* espera pelos threads fill() */
                printf("count[%d] = %d\n", k, count[k]);
        }

        pthread_join(tidv, NULL);
        return 0;
}

void *fill(void *nr) {
        while (1) {
                pthread_mutex_lock(&mut);
                if (pos >= npos) {
                        pthread_mutex_unlock(&mut);
                        return NULL;
                }
                buf[pos] = val;
                pos++; val++;
                pthread_mutex_unlock(&mut);
                *(int *)nr += 1;
        }
}

/* thread verificador */
void *verify(void *arg) {
        int k;
        for (k=0; k < npos; k++) {
                pthread_mutex_lock(&mut);
                while (k > pos)
                        pthread_cond_wait(&cvar, &mut);
                if(k < pos) {
                        if (buf[k] != k) { /* escreve se encontrar valores errados */
                                printf("buf[%d] = %d\n", k, buf[k]);
                        }
                }
                pthread_mutex_unlock(&mut);
        }
        return NULL;
}
