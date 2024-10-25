#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <memory.h>
#include <fcntl.h>
int global = 0;

int main() {
    pid_t children[8] = {0};
    pid_t father = 0;
    
    int* counter = calloc(sizeof(int),1);
    int fd;
    for (int i=0; i<2; i++) {
        pid_t p = fork();
        if(p == 0) {
            //child
            fd = open("many_lines",O_RDONLY);
            printf("My FD: %d CHILD %d\n", fd, getpid());
            break;

        } else {
            children[i] = p;
            father = getpid();
        }
    }

    if (father != getpid()) {
        char buff[100];
        while(read(fd, &buff[0], 99) != 0) {
            buff[99] = '\0';
            printf("PID %d: %s\n", getpid(), &buff[0]);
            sleep(2);
        }
        
    } else {
        while(1) {
            int status;
            pid_t ch = waitpid(-1,&status,0);
            printf("I am the parent, reaped my child  PID %d\n", ch);
            if (ch == -1) {
                exit(0);
            }
        } 
    }
    return 0;
}

    
