#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>

void sigint_handler(int signo) {
	printf("Entering SIGINT handler ...\n");
	sleep(10);
	printf("Exiting SIGINT handler ...\n");
}

void sigterm_handler(int signo) {
	printf("Entering SIGTERM handler ...\n");
	sleep(10);
	printf("Exiting SIGTERM handler ...\n");
}

int main(void) {
	struct sigaction action;
	action.sa_handler = sigint_handler;
	sigemptyset(&action.sa_mask);
	action.sa_flags = 0;

	if (sigaction(SIGINT,&action,NULL) < 0) {
		fprintf(stderr,"Unable to install SIGINT handler\n");
		exit(1); 
}
	struct sigaction term_action;
	term_action.sa_handler = sigterm_handler;
	sigemptyset(&term_action.sa_mask);
	term_action.sa_flags = 0;

	if (sigaction(SIGTERM,&term_action,NULL) < 0) {
		fprintf(stderr,"Unable to install SIGTERM handler\n");
		exit(1); 
}

	printf("Try me with CTRL-C ...\n");
	while(1) pause();
	exit(0); 
}
