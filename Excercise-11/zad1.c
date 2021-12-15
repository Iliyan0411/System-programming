#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>


int main(int argc, char **argv)
{
    int fd[2];
    if(pipe(fd) == -1){
        perror("Pipe error");
        exit(-1);
    }

    int pid = fork();

    if(pid < 0){
        perror("Fork error");
        exit(-1);
    }
    else if(pid > 0){
        int status;
        wait(&status);
        
        if(status == 0){
            close(0);
            dup(fd[0]);
            close(fd[0]);
            close(fd[1]);

            execlp("wc", "wc", "-l", (char *)0);
        }

        perror("An error has occured");
        exit(-1);
    }
    else{
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);

        exit(execlp("who", "who", (char *)0));
    }


    return 0;
}