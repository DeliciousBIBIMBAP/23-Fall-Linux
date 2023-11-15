#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define MAXLINE 100

int main() {
	int fd, length, i;
	char massage[MAXLINE];
	sprintf(massage, "Hello From PID %d", getpid());
	length = strlen(massage) + 1;
	do {
		fd = open("myPipe", O_WRONLY);
		if (fd == -1) sleep(1);
	} while (fd == -1);
	
	for (i = 0; i <= 3; i++) {
		write(fd, massage, length);
		sleep(3);
	}
	close(fd);
	return 0;
}