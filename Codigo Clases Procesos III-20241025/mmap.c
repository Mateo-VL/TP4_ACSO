#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 #include <sys/wait.h>
 #include <sys/mman.h>
#include <string.h>
int main() {
    pid_t children[8] = {0};
    pid_t father = 0;
   
    char* str = mmap(NULL, 100, PROT_READ | PROT_WRITE,
            MAP_SHARED | MAP_ANONYMOUS,-1,0);
    pid_t p = fork();
    if(p == 0) {
        //child
        printf("Child PID: %d\n", getpid());
        char* msg = "Child message sent\n";
        int size = strlen(msg)+1;
        memmove(str,msg,size);
    } else {
        children[0] = p;
        father = getpid();
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
       printf("Parent %d, %s\n", getpid(), str);
    }
    return 0;
}

    
