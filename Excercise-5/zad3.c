#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <wait.h>


int main(int argc, char **argv)
{
    int pid = fork(), status = 0;

    if(pid == -1){
        perror("Something went wrong with fork() command.\n");
        exit(-1);
    }
    else if(pid > 0){
        wait(&status);

        if(status >= 0){
            write(1, argv[1], strlen(argv[1])+1);
        }
    }
    else{
        exit(execlp(argv[1], argv[1], (char *)0));
    }


    return 0;
}