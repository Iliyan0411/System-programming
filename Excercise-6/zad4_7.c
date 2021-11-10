#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
        int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
        int fd1 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);

        int pid = fork(), status = 0, temp_fd1, temp_1;

        if(pid == -1){
                perror("Error!\n");
                exit(-1);
        }
        else if(pid > 0){
                wait(&status);
                write(fd, "hello1", 6);
                close(fd);
        }
        else{
                temp_1 = dup(1);
                close(1);
                temp_fd1 = dup(fd1);

                write(1, "hello2", 6);

                dup(temp_1);
                dup(temp_fd1);
        }

        write(temp_1, "hello3", 6);
        write(fd1, "hello4", 6);


        return 0;
}
