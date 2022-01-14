#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
    int pid1;
    if((pid1 = fork()) == -1){
        write(1, "Error with fork command!\n", 25);
        exit(-1);
    }
    else if(pid1 > 0){
        int status1;
        wait(&status1);

        if(status1 == 0){
            execlp("mv", "mv", argv[1], "./..", (char *)0);
        }
    }
    else{
        int fds[2];
        if(pipe(fds) == -1){
            write(1, "Error with pipe command!\n", 25);
            exit(-1);
        }

        int fd = open(argv[1], O_WRONLY|O_CREAT|O_TRUNC, 0666);

        int pid2;
        if((pid2 = fork()) == -1){
            write(1, "Error with fork command!\n", 25);
            exit(-1);
        }
        else if(pid2 > 0){
            int status2;
            wait(&status2);

            close(0);
            dup(fds[0]);

            close(1);
            dup(fd);

            close(fds[0]);
            close(fds[1]);
            close(fd);
            
            exit(execlp("grep", "grep", "vim", (char *)0));
        }
        else{
            close(1);
            dup(fds[1]);

            close(fds[0]);
            close(fds[1]);
            close(fd);

            exit(execlp("ps", "ps", "aux", (char *)0));
        }
    }


    return 0;
}