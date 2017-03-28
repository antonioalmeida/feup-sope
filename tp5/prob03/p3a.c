#include <stdio.h>
#include <stdlib.h>
#define MAXLINE 1000
#define SORT "/usr/bin/sort" // macOS

int main(int argc, char *argv[]) {
        char line[MAXLINE];
        FILE *fpin, *fpout;

        if (argc != 2) {
                printf("usage: %s filename\n", argv[0]);
                exit(1);
        }

        // Opening file
        if ((fpin = fopen(argv[1], "r")) == NULL) {
                fprintf(stderr, "can't open %s", argv[1]);
                exit(1);
        }

        // Opening sort "file" as pipe to write to
        if ((fpout = popen(SORT, "w")) == NULL) {
                fprintf(stderr, "popen error");
                exit(1);
        }

        while (fgets(line, MAXLINE, fpin) != NULL) // Reading line from input file
                fputs(line, fpout);          // Writing line to sort

        pclose(fpout);
        exit(0);
}
