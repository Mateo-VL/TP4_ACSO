#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 #include <sys/wait.h>

int main() {
    pid_t children[8] = {0};
    pid_t father = 0;
    for (int i=0; i<8; i++) {
        pid_t p = fork();
        if(p == 0) {
            if(i ==0) sleep(5);
            //child
            printf("Child number #%d, PID: %d", i, getpid());
            break;
        } else {
            children[i] = p;
            father = getpid();
        }
    }

    if (father != getpid()) {
        printf("I am a child with PID %d, my parent is: %d\n", getpid(), getppid()); 
    } else {
        for (int i=0; i<8; i++) {
            int status;
            pid_t ch = waitpid(children[i],&status,0);
            printf("I am the parent, reaped my child  PID %d\n", ch);
            if (ch == -1) {
                exit(0);
            }
        }
    }
    return 0;
}

    
