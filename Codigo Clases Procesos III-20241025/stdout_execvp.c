#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
 #include <sys/wait.h>

int main() {
    pid_t children[8] = {0};
    pid_t father = 0;

    int pipefd[2];
    pipe(pipefd);
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
        close(pipefd[0]); // No reading for child
        dup2(pipefd[1], STDOUT_FILENO);
        close(pipefd[1]);
        char* args[3] = {"ls","-alh", NULL};
        execvp(args[0],args);

        printf("EXECVP ERROR\n");
    } else {

        while(1) {
            int status;
            pid_t ch = waitpid(-1,&status,0);
            char arr[400];
            close(pipefd[1]); //No writing for parent
            int curr = read(pipefd[0], arr, 400);
            arr[curr]='\0';
            close(pipefd[0]);
            printf("CHILD MSG\n %s, \n I am parent\n", arr);
            break;
        } 
    }
    return 0;
}

    
