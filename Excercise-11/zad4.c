#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>


int main(int argc, char **argv)
{
    int fd1[2];
    if(pipe(fd1) == -1){
        perror("Pipe_1 erorr");
        exit(-1);
    }

    int pid1 = fork();
    if(pid1 < 0){
        perror("Fork_1 error");
        exit(-1);
    }
    else if(pid1 > 0){
        int status;
        wait(&status);

        if(status == 0){
            close(0);
            dup(fd1[0]);
            close(fd1[0]);
            close(fd1[1]);

            execlp(argv[3], argv[3], (char *)0);
        }

        perror("Status_1 error has ocuured");
        exit(-1);
    }
    else{
        int fd2[2];
        if(pipe(fd2) == -1){
            perror("Pipe_2 error");
            exit(-1);
        }

        int pid2 = fork();
        if(pid2 < 0){
            perror("Fork_2 error");
            exit(-1);
        }
        else if(pid2 > 0){
            int status;
            wait(&status);

            if(status == 0){
                close(1);
                dup(fd1[1]);
                close(0);
                dup(fd2[0]);
                close(fd2[0]);
                close(fd2[1]);

                exit(execlp(argv[2], argv[2], (char *)0));
            }

            perror("Status_2 error has ocuured");
            exit(-1);
        }
        else{
            close(1);
            dup(fd2[1]);
            close(fd2[0]);
            close(fd2[1]);

            exit(execlp(argv[1], argv[1], (char *)0));
        }
    }


    return 0;
}