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
            //child
            break;
        } else {
            children[i] = p;
            father = getpid();
        }
    }

    if (father != getpid()) {
        printf("I am a child with PID %d, my parent is: %d\n", getpid(), getppid()); 
    } else {
        sleep(10);
//        while (1) {
//            int status;
//            if(waitpid(-1,&status, 0) == -1) {
//                exit(0);
//            }
//        }         
   }
    return 0;
}

    
