#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 #include <sys/wait.h>
#include <string.h>
int main() {
    pid_t children[8] = {0};
    pid_t father = 0;
    
    int pipefd[2];
    pipe(pipefd);
    pid_t p = fork();
    if(p == 0) {
        //child
        close(pipefd[0]);
        dup2(pipefd[1], STDOUT_FILENO);
        char* msg = "Child message sent\n";
        int count, size;
        printf("PID Child %d, %s\n", getpid(), msg);        
        close(pipefd[1]);
    } else {
        close(pipefd[1]);
        int size = 100;
        char buf[size];
        int count = 0;
        while(1) {
            int temp = read(pipefd[0],&buf[0] + count,size);
            if(!temp) break;
            count += temp;
        }
        printf("parent %d, MSG: %s",getpid(), &buf[0]);
        children[0] = p;
        father = getpid();
        close(pipefd[0]);
    }

    if (father != getpid()) {
      //  printf("I am a child with PID %d, my parent is: %d\n", getpid(), getppid()); 
    } else {
            int status;
            pid_t ch = waitpid(children[0],&status,0);
            printf("I am the parent, reaped my child  PID %d\n", ch);
            if (ch == -1) {
                exit(0);
            }
        }
    return 0;
}

    
