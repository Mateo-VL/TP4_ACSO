#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <memory.h>
#include <fcntl.h>
int global = 0;

#define BUFFER_SIZE 100
int main() {
    pid_t children[8] = {0};
    pid_t father = 0;
    
    int* counter = calloc(sizeof(int),1);

    int fd = open("many_lines",O_RDONLY);
    for (int i=0; i<2; i++) {
        pid_t p = fork();
        if(p == 0) {
            //child
            break;
        } else {
            children[i] = p;
            father = getpid();
        }
    }

    if (father != getpid()) {
        char buff[BUFFER_SIZE];
        while(read(fd, &buff[0],BUFFER_SIZE -1) != 0) {
            buff[BUFFER_SIZE-1] = '\0';
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

    
