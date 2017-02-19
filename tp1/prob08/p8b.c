#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include <time.h>
#include <string.h>

int main(int argc, const char** argv) {
   //Seeding random number generator 
   srand((unsigned) time(NULL));

   struct tms t;

   clock_t start_t, end_t, total_t;

   int max = (int)strtol(argv[1], NULL, 10);
   int target = (int)strtol(argv[2], NULL, 10);

   int currentValue = -1;
   int counter = 0;

   start_t = clock();
   while(currentValue != target) {
       currentValue = rand() % max;
       printf("%d = %d\n", counter, currentValue);
       counter++;
   }
   end_t = clock();

   total_t = end_t - start_t;

   printf("\nComplete after %d iterations!\n", counter);
   printf("CPU Ticks : %d\n", total_t);
   printf("Time taken : %f seconds\n", (double)(total_t / (double)CLOCKS_PER_SEC));
   printf("CPU user time : %f seconds\n", (double)t.tms_cutime/ (double)CLOCKS_PER_SEC);
   printf("CPU system time : %f seconds\n", (double)t.tms_cstime/ (double)CLOCKS_PER_SEC);
   exit(0);
}
