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

            execlp(argv[2], argv[2], (char *)0);
        }

        perror("An error has ocuured");
        exit(-1);
    }
    else{
        close(1);
        dup(fd[1]);
        close(fd[0]);
        close(fd[1]);

        exit(execlp(argv[1], argv[1], (char *)0));
    }


    return 0;
}