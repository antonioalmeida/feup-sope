#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#define READ 0
#define WRITE 1

typedef struct {
  int n1;
  int n2;
} Pair;

int main(void) {
  int fd[2];
  pid_t pid;
  pipe(fd);

  if( (pid = fork()) < 0) {
    fprintf(stderr,"fork error\n");
    exit(1);
  }

  if (pid >0) { //Parent
    Pair p;
    printf( "PARENT:\n" );
    printf( "x y ? " );
    scanf( "%d %d" , &p.n1, &p.n2);
    close(fd[READ]); // read pipe isn't used at all
    write(fd[WRITE], &p, sizeof(Pair));
    close(fd[WRITE]); // close write pipe
  }
  else { //Son
    Pair p2;
    close(fd[WRITE]);
    read(fd[READ], &p2, sizeof(Pair));
    printf( "SON:\n" );

    printf( "x + y = %d\n", p2.n1 + p2.n2);
    printf( "x - y = %d\n", p2.n1 - p2.n2);
    printf( "x * y = %d\n", p2.n1 * p2.n2);
    printf( "x / y = %d\n", p2.n1 / p2.n2);
    close(fd[READ]);
  }

  return 0;
}
