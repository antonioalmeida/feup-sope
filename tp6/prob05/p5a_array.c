#include <pthread.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

#define OPERAND_0 0
#define OPERAND_1 1
#define NUM_THREADS 4

void *sumFunction(void *argv) {
        int* argvInt = (int *) argv;

        int arg0 = argvInt[0];
        int arg1 = argvInt[1];
        int result = arg0 + arg1;

        printf("%d + %d = %d\n", arg0, arg1, result);
        return NULL;
}

void *subFunction(void *argv) {
        int* argvInt = (int *) argv;

        int arg0 = argvInt[0];
        int arg1 = argvInt[1];
        int result = arg0 - arg1;

        printf("%d - %d = %d\n", arg0, arg1, result);
        return NULL;
}

void *quoFunction(void *argv) {
        int* argvInt = (int *) argv;

        int arg0 = argvInt[0];
        int arg1 = argvInt[1];
        int result = arg0 / arg1;

        printf("%d / %d = %d\n", arg0, arg1, result);
        return NULL;
}

void *prodFunction(void *argv) {
        int* argvInt = (int *) argv;

        int arg0 = argvInt[0];
        int arg1 = argvInt[1];
        int result = arg0 * arg1;

        printf("%d * %d = %d\n", arg0, arg1, result);
        return NULL;
}

int main() {
        pthread_t threads[NUM_THREADS];

        int input[2];
        printf("Please write two numbers, separated by a space : ");
        scanf("%d %d", input, &input[1]);

        printf("Teste : %d %d\n", input[0], input[1]);

        pthread_create(&threads[0], NULL, sumFunction, &input);
        pthread_create(&threads[1], NULL, subFunction, &input);
        pthread_create(&threads[2], NULL, quoFunction, &input);
        pthread_create(&threads[3], NULL, prodFunction, &input);

        pthread_exit(0);
}
