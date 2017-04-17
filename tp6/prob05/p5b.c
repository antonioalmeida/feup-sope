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
        int* result = malloc(sizeof(int));
        *result = arg0 + arg1;

        return result;
}

void *subFunction (void *argv) {
        Data argvInt = *((Data *)argv);

        int arg0 = argvInt.op1;
        int arg1 = argvInt.op2;
        int* result = malloc(sizeof(int));
        *result = arg0 - arg1;

        return result;
}

void *quoFunction (void *argv) {
        Data argvInt = *((Data *)argv);

        int arg0 = argvInt.op1;
        int arg1 = argvInt.op2;
        int* result = malloc(sizeof(int));
        *result = arg0 / arg1;

        return result;
}

void *prodFunction (void *argv) {
        Data argvInt = *((Data *)argv);

        int arg0 = argvInt.op1;
        int arg1 = argvInt.op2;
        int* result = malloc(sizeof(int));
        *result = arg0 * arg1;

        return result;
}

int main () {
        pthread_t threads[NUM_THREADS];

        Data input;

        printf("Please write two numbers, separated by a space : ");
        scanf("%d %d", &input.op1, &input.op2);

        printf("Teste : %d %d\n", input.op1, input.op2);

        void* returnValue;

        pthread_create(&threads[0], NULL, sumFunction, &input);
        pthread_join(threads[0], &returnValue);
        printf("%d + %d = %d\n", input.op1, input.op2, *((int *)returnValue));

        pthread_create(&threads[1], NULL, subFunction, &input);
        pthread_join(threads[1], &returnValue);
        printf("%d - %d = %d\n", input.op1, input.op2, *((int *)returnValue));

        pthread_create(&threads[2], NULL, quoFunction, &input);
        pthread_join(threads[2], &returnValue);
        printf("%d / %d = %d\n", input.op1, input.op2, *((int *)returnValue));

        pthread_create(&threads[3], NULL, prodFunction, &input);
        pthread_join(threads[3], &returnValue);
        printf("%d * %d = %d\n", input.op1, input.op2, *((int *)returnValue));

        pthread_exit(0);
}
