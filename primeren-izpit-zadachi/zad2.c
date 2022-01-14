#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
    if(argc != 3){
        write(1, "Wrong number of arguments!\n", 27);
        exit(-1);
    }

    int fd1 = open(argv[1], O_RDONLY);
    int fd2 = open(argv[2], O_WRONLY|O_CREAT, 0666);

    int fd[2];
    if(pipe(fd) == -1){
        write(1, "Error with pipe command!\n", 25);
        exit(-1);
    }

    int pid;
    if((pid = fork()) == -1){
        write(1, "Error with fork command!\n", 25);
        exit(-1);
    }
    else if(pid > 0){
        int status;
        wait(&status);

        close(0);
        dup(fd[0]);

        close(1);
        close(2);
        dup(fd2);

        close(fd[0]);
        close(fd[1]);
        close(fd1);
        close(fd2);

        execlp("grep", "grep", "pts", (char *)0);
    }
    else{
        close(1);
        dup(fd[1]);

        close(0);
        dup(fd1);

        close(fd[0]);
        close(fd[1]);
        close(fd1);
        close(fd2);

        exit(execlp("cat", "cat", (char *)0));
    }


    return 0;
}