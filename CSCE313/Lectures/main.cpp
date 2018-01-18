#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
	int n;
	for(int n = 0; n < 5; n++) {
		printf("my pid: %d, n = %d\n",getpid(),n);
		sleep(1);
		if(fork() != 0) {
			exit(0);
		}
	}
}
