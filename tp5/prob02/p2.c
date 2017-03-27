#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

#define READ 0
#define WRITE 1

#define INT 0
#define FLOAT 1

typedef struct {
  int sum;
  int diff;
  int prod;
  float quoFloat;
  int quoInt;
  int QUO_TYPE;
} Data;

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

    write(fd[WRITE],a,2* sizeof ( int ));
    close(fd[WRITE]); // close write pipe

    wait(NULL); // waiting for son to finish

    Data resultParent;
    read(fd[READ], &resultParent, sizeof(Data));
    printf( "x + y = %d\n", resultParent.sum);
    printf( "x - y = %d\n", resultParent.diff);
    printf( "x * y = %d\n", resultParent.prod);

    if(resultParent.QUO_TYPE == INT)
    printf( "x / y = %d\n",resultParent.quoInt);
    else
    printf( "x / y = %f\n",resultParent.quoFloat);
    close(fd[READ]);
  }
  else { //Son
    int b[2];
    read(fd[READ],b,2* sizeof ( int ));
    close(fd[READ]);
    printf( "SON:\n" );

    Data result;
    result.sum = b[0] + b[1];
    result.diff = b[0] - b[1];
    result.prod = b[0] * b[1];

    if(b[0] % b[1] == 0) {
      result.QUO_TYPE = INT;
      result.quoInt = b[0] / b[1];
    }
    else {
      result.QUO_TYPE = FLOAT;
      result.quoFloat = b[0] / b[1];
    }

    write(fd[WRITE], &result, sizeof(Data));
    close(fd[WRITE]);
  }

  return 0;
}
