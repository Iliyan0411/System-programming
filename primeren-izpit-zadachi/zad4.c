#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int pid1, pid2;
    if((pid1 = fork())){
        if((pid2 = fork())){
            int status1, status2;
            waitpid(pid2, &status2, 0);
            waitpid(pid1, &status1, 0);

            printf("Return code 1: %d\nReturn code 2: %d\n", status1, status2);
        }
        else{
            exit(execlp(argv[1], argv[1], (char *)0));
        }
    }
    else{
        exit(execvp(argv[2], &argv[2]));
    }


    return 0;
}