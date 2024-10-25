#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <memory.h>
#include <fcntl.h>
int global = 0;

int main() {
    int fd = open("many_lines",O_RDONLY);
        char buff[100];
        while(read(fd, &buff[0], 99) != 0) {
            buff[99] = '\0';
            printf("PID %d: %s\n", getpid(), &buff[0]);
        }
        return 0;
}
    
