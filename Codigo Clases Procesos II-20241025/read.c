#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <memory.h>
#include <fcntl.h>

int main() {
       int sz_arr = 100;
       char input[sz_arr];
       int curr = 0;
       int total = 0;
       curr = read(STDIN_FILENO, input, sz_arr);
       if (curr == -1) {
           perror("error in main read: ");
           return -1;
       }
       input[curr] = '\0'; 
       printf("HERE : %s\n", input);

       return 0;
}
    
