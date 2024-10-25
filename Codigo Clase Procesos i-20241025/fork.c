#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 #include <sys/wait.h>

int main() {
    pid_t children[8] = {0};
    pid_t parent = 0;
    for (int i=0; i<8; i++) {
        pid_t p = fork();
        if(p == 0) {
            //child
            if (i ==0){
                sleep(4);
            }
            break;
        } else {
            children[i] = p;
            parent = getpid();
        }
    }

    if (getpid() != parent) {
        printf("I am a child with PID %d, my parent is: %d\n", getpid(), getppid()); 
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

    
