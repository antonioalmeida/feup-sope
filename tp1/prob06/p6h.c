// PROGRAMA p6a.c
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#define BUF_LENGTH 256
int main(int argc, char** argv)
{
    FILE *src, *dst;

    if(argc != 3)
        printf("usage: nome_do_executavel file1 file2\n");
    
    char* srcFile = argv[1]; 
    char* dstFile = argv[2];


    char buf[BUF_LENGTH];
    if( (src = fopen( srcFile, "r" ) ) == NULL )
    {
        printf("%d\n", errno);
        exit(1);
    }
    if ( ( dst = fopen( dstFile, "w" ) ) == NULL )
    {
        printf("%d\n", errno);
        exit(2);
    }
    while( ( fgets( buf, BUF_LENGTH, src ) ) != NULL )
    {
        fputs( buf, dst );
    }
    fclose( src );
    fclose( dst );
    exit(0);  // zero é geralmente indicativo de "sucesso"
}
