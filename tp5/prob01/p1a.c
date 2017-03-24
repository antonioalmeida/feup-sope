#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#define READ 0
#define WRITE 1

int main(void) {
  int fd[2];
  pid_t pid;
  pipe(fd);

  if( (pid = fork()) < 0) {
    fprintf(stderr,"fork error\n");
    exit(1);
  }

  if (pid >0) { //Parent
    int a[2];
    printf( "PARENT:\n" );
    printf( "x y ? " );
    scanf( "%d %d" ,&a[0],&a[1]);
    close(fd[READ]); // read pipe isn't used at all
    write(fd[WRITE],a,2* sizeof ( int ));
    close(fd[WRITE]); // close write pipe
  }
  else { //Son
    int b[2];
    close(fd[WRITE]);
    read(fd[READ],b,2* sizeof ( int ));
    printf( "SON:\n" );

    printf( "x + y = %d\n", b[0] + b[1]);
    printf( "x - y = %d\n", b[0] - b[1]);
    printf( "x * y = %d\n", b[0] * b[1]);
    printf( "x / y = %d\n", b[0] / b[1]);
    close(fd[READ]);
  }

  return 0;
}
