#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 #include <sys/wait.h>

int main() {
    pid_t children[8] = {0};
    pid_t parent = 0;
    pid_t p = fork();
    if(p == 0) {
        //child
        printf("I am child %d, parent == %d\n", getpid(),getppid());
    } else {
        printf("I am parent %d, child == %d\n", getpid(), p);
    }

    return 0;
}

    
