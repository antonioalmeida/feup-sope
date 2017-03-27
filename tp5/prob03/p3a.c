#include
<stdio.h>
#include
<stdlib.h>
#define
   MAXLINE   1000
#define
   PAGER
"/bin/more"
int
 main(
int
 argc,
char
 *argv[])
{
char
   line[MAXLINE];
      FILE   *fpin, *fpout;
if
 (argc != 2) { printf(
"usage: %s filename\n"
,argv[0]); exit(1); }
if
 ((fpin = fopen(argv[1],
"r"
)) == NULL)
      {
            fprintf(stderr,
"can't open %s"
, argv[1]); exit(1);
      }
if
 ((fpout = popen(PAGER,
"w"
)) == NULL)
      {
            fprintf(stderr,
"popen error"
); exit(1);
      }
/* copy filename contents to pager - file=argv[1] */
while
 (fgets(line, MAXLINE, fpin) != NULL)
      {
if
 (fputs(line, fpout) == EOF)
            {
                  printf(
"fputs error to pipe"
); exit(1);
            }
      }
if
 (ferror(fpin))
      {
            fprintf(stderr,
"fgets error"
); exit(1);
      }
if
 (pclose(fpout) == -1)
      {
            fprintf(stderr,
"pclose error"
);
            exit(1);      }
      exit(0);
} 
