#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/wait.h>
#include <memory.h>
#include <fcntl.h>
int global = 0;

int main() {
       write(STDOUT_FILENO, "HELLO WORLD\n", 13);
       return 0;
}
    
