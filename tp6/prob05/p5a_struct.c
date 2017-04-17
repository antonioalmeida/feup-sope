#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define OPERAND_0 0
#define OPERAND_1 1
#define NUM_THREADS 4

typedef struct {
        int op1;
        int op2;
} Data;

void *sumFunction (void *argv) {
        Data argvInt = *((Data *)argv);

        int arg0 = argvInt.op1;
        int arg1 = argvInt.op2;
        int result = arg0 + arg1;

        printf("%d + %d = %d\n", arg0, arg1, result);
        return NULL;
}

void *subFunction (void *argv) {
        Data argvInt = *((Data *)argv);

        int arg0 = argvInt.op1;
        int arg1 = argvInt.op2;
        int result = arg0 - arg1;

        printf("%d - %d = %d\n", arg0, arg1, result);
        return NULL;
}

void *quoFunction (void *argv) {
        Data argvInt = *((Data *)argv);

        int arg0 = argvInt.op1;
        int arg1 = argvInt.op2;
        int result = arg0 / arg1;

        printf("%d / %d = %d\n", arg0, arg1, result);
        return NULL;
}

void *prodFunction (void *argv) {
        Data argvInt = *((Data *)argv);

        int arg0 = argvInt.op1;
        int arg1 = argvInt.op2;
        int result = arg0 * arg1;

        printf("%d * %d = %d\n", arg0, arg1, result);
        return NULL;
}

int main () {
        pthread_t threads[NUM_THREADS];

        Data input;

        printf("Please write two numbers, separated by a space : ");
        scanf("%d %d", &input.op1, &input.op2);

        printf("Teste : %d %d\n", input.op1, input.op2);

        pthread_create(&threads[0], NULL, sumFunction, &input);
        pthread_create(&threads[1], NULL, subFunction, &input);
        pthread_create(&threads[2], NULL, quoFunction, &input);
        pthread_create(&threads[3], NULL, prodFunction, &input);

        pthread_exit(0);
}
