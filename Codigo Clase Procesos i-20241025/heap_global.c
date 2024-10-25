#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <memory.h>
int global = 0;

int main() {
    pid_t children[8] = {0};
    pid_t father = 0;
    
    int* counter = calloc(sizeof(int),1);

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
        printf("child %d, my counter is %d, global: %d\n", getpid(), *counter, global);
        *counter +=1;
        global +=1;
        printf("child %d, my counter is %d, global: %d\n", getpid(), *counter, global);
        *counter +=1;
        global +=1;
        printf("child %d, my counter is %d, global: %d\n", getpid(), *counter, global);
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

    
