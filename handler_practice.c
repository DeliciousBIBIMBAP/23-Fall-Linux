#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
void intHandler();
void intHandler2();
void intHandler3();
void print_gugu();

int child_id;

void print_gugu() {
	for (int i = 1; i <= 20; i++ ) {
		for (int j = 1; j <= 9; j++) {
			printf("%d X %d = %d \n", i, j, i * j);
		}
		printf("\n");
		if (i == 9) {
			signal(SIGINT, intHandler3);
		}
		sleep(1);
	}
}
int main() {
	int pid;
	if ((pid = fork()) == 0) {
		signal(SIGINT, intHandler2);
		print_gugu();
	}
	else {
		child_id = pid;
		signal(SIGINT, intHandler);
		wait();
	}
}
void intHandler(int signo) {
	kill(child_id, SIGINT);
}
void intHandler2(int signo) {
	printf("\n구구단 실행 중이니 종료 불가\n");
}
void intHandler3(int signo) {
	kill(-getppid(), SIGKILL);
}
