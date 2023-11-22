#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>
void intHandler();
void intHandler2();
void quizGame();
#define PASSWORD 123
int input;

void quizGame() {
	signal(SIGINT, intHandler);
	alarm(10);
	signal(SIGALRM, intHandler2);
	while (1) {
		scanf("%d", &input);
		if (input == PASSWORD) {
			prtinf("correct !\n");
			exit(0);
		}
	}
}
int main() {
	quizGame();
}
void intHandler(int signo) {
	printf("10 sec rest...\n");
	quizGame();
}
void intHandler2(int signo) {
	printf("Fire !\n");
	exit(0);
}