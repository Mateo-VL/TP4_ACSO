#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 #include <sys/wait.h>

int main() {
    pid_t children[8] = {0};
    pid_t father = 0;
    for (int i=0; i<1; i++) {
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
        char* args[3] = {"ls","-alh", NULL};
        execvp(args[0],args);

        printf("EXECVP ERROR\n");
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

    
