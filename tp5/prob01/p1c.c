#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#define READ 0
#define WRITE 1
#define MAX_LENGTH 256

int main(void) {
  int fd[2];
  pid_t pid;
  pipe(fd);

  if( (pid = fork()) < 0) {
    fprintf(stderr,"fork error\n");
    exit(1);
  }

  if (pid >0) { //Parent
    char n1[MAX_LENGTH];
    char n2[MAX_LENGTH];

    printf( "PARENT:\n" );
    printf( "x y ? " );
    scanf( "%s %s" , n1, n2);
    close(fd[READ]); // read pipe isn't used at all
    write(fd[WRITE], n1, MAX_LENGTH);
    write(fd[WRITE], n2, MAX_LENGTH);
    close(fd[WRITE]); // close write pipe
  }
  else { //Son
    char n1Son[MAX_LENGTH];
    char n2Son[MAX_LENGTH];
    int n;

    close(fd[WRITE]);
    n = read(fd[READ],n1Son, MAX_LENGTH); n1Son[n] = 0;
    n = read(fd[READ],n2Son, MAX_LENGTH); n2Son[n] = 0;
    printf( "SON:\n" );

    int n1Int = atoi(n1Son);
    int n2Int = atoi(n2Son);

    printf( "x + y = %d\n", n1Int + n2Int);
    printf( "x - y = %d\n", n1Int - n2Int);
    printf( "x * y = %d\n", n2Int * n2Int);
    printf( "x / y = %d\n", n2Int / n2Int);
    close(fd[READ]);
  }

  return 0;
}
