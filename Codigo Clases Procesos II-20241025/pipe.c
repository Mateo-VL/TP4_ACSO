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
        //child writes
        printf("Child PID: %d\n", getpid());
       close(pipefd[0]);  //Close pipe for reading child doesnt read
       char* msg = "Child message sent\n";
       int count, size;
        count =0;
        size = strlen(msg)+1;
        while(count != size) {
           count +=  write(pipefd[1],msg + count, size - count);
        }
        close(pipefd[1]); // sends EOF
    } else {
        close(pipefd[1]); //Close write pipe, parent doesnt write
        int size = 100;
        char buf[size];
        int count = 0;
        while(1) {
            int temp = read(pipefd[0],&buf[0] + count,size);
            if(!temp) break;
            count += temp;
        }
        printf("father %d, %s",getpid(), &buf[0]);
        children[0] = p;
        father = getpid();
        close(pipefd[0]);
    }

    if (father != getpid()) {
        printf("I am a child with PID %d, my parent is: %d\n", getpid(), getppid()); 
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

    
