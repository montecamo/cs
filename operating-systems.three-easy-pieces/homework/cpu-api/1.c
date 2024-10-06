#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>

#define SIZE 14
char *msg1 = "hello world 1";
char *msg2 = "hello world 1";

int main(int argc, char *argv[]) {
    char *buf[0];

    read(1, buf, 0);
    printf("Done\n");

    return 0;
}


