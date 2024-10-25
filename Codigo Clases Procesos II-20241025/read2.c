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
       do {
           curr = read(STDIN_FILENO, input + total, sz_arr - total);
           if (curr == -1) {
               perror("error in main read: ");
               return -1;
           }
           total += curr;
       } while (curr && (total < sz_arr));

       
       printf("HERE : %s\n", input);

       return 0;
}
    
