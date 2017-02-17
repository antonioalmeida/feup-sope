#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char* getenv(const char* name);
//Before running this program, run $ export USER_NAME="Example Name"
int main(int argc, char** argv) {
    char* name = getenv("USER_NAME");
	printf("Hello %s!\n", name);
	return 0;
}
