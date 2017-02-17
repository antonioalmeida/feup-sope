#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

extern char* getenv(const char* name);
int main(int argc, char** argv) {
    char* name = getenv("USER");
	printf("Hello %s!\n", name);
	return 0;
}
