#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void intHandler();
int main() {
	alarm(5);
	signal(SIGALRM, intHandler);
	printf("loop...\n");
	while (1) {
		sleep(1);
		printf("1 sec... \n");
	}
	printf("End of main. \n");
}
void intHandler() {
	printf("Wake Up!\n");
	exit(0);
}