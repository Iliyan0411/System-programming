#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd1 = open(argv[1], O_WRONLY | O_TRUNC | O_CREAT, 0644);
    int fd2 = dup(fd1);

    int pid1 = fork(), status1, status2;

    if (pid1 == -1)
    {
        perror("Somerhing went wrong.\n");
        exit(-1);
    }
    else if (pid1 > 0)
    {
        wait(&status1);

        int pid2 = fork();

        if (pid2 == -1)
        {
            perror("Somerhing went wrong.\n");
            exit(-1);
        }
        else if (pid2 > 0)
        {
            wait(&status2);
            close(fd1);
            close(fd2);
        }
        else
        {
            write(fd2, "Hello", 5);
        }
    }
    else
    {
        write(fd1, "Hello", 5);
    }

    return 0;
}