#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

int main() {

if (fork() == 0) {
if(fork() == 0) {
printf("3");
}
}

else {
if (fork() == 0) {
printf("1");
exit(0);
}
printf("2");
}
printf("0");
return 0;
}
