#include <stdio.h>
#include <termios.h>
#include <stdlib.h>
#include <unistd.h>
#define MAX_INPUT 256

int main(void) {
   struct termios tms; 

   tcgetattr(STDIN_FILENO, &tms); // Read the console's current definitions
   tms.c_lflag &= ~(ICANON | ECHO); //Activate raw mode
   tcsetattr(STDIN_FILENO, TCSANOW, &tms);

   write(STDOUT_FILENO, "Insert a password : ", 20);

   char* input = (char*)malloc(MAX_INPUT);
   int index = 0;
   do {
       read(STDIN_FILENO, (input + index++), 1);
       write(STDOUT_FILENO, "*", 1);
   } while(input[index-1] != '\n');

   input[--index] = 0;
    
   printf("\nThe password is %s\n", input);
   return 0;
}
