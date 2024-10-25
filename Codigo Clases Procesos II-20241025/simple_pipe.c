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
    char* msg = "Child message sent\n";
    int count, size;
    count =0;
    size = strlen(msg)+1;
    while(count != size) {
        count +=  write(pipefd[1],msg + count, size - count);
    }
    close(pipefd[1]);
    size = 100;
    char buf[size];
    count = 0;
    while(1) {
        int temp = read(pipefd[0],&buf[0] + count,size);
        if(!temp) break;
        count += temp;
    }
    close(pipefd[0]);
    printf("my message: %s", &buf[0]);
    return 0;
}

    
