#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_ITERATIONS 5000

int main(int argc, const char** argv) {
   /* Intializes random number generator */
   srand((unsigned) time(NULL));

   int max = (int)strtol(argv[1], NULL, 10);
   int target = (int)strtol(argv[2], NULL, 10);

   int currentValue = -1;
   int counter = 0;
   while(currentValue != target || counter == MAX_ITERATIONS) {
       currentValue = rand() % max;
       printf("%d = %d\n", counter, currentValue);
       counter++;
   }

   exit(0);
}
