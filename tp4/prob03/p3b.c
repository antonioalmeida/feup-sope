#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000
#define SORT "/usr/bin/sort" // macOS !!

// Run this in pipe with cat, like
// $ cat filename.txt | ./p3b

int main(int argc, char *argv[]) {
  char line[MAXLINE];
  FILE *fpout;

  // Opening sort "file" as pipe to write to
  if ((fpout = popen(SORT, "w")) == NULL) {
    fprintf(stderr, "popen error");
    exit(1);
  }

  while (fgets(line, MAXLINE, stdin) !=
         NULL)          // Reading line from stdin (cat command's output)
    fputs(line, fpout); // Writing line to sort

  pclose(fpout);
  exit(0);
}
