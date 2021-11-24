#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
        int fd1;
        if ((fd1 = open(argv[1], O_RDWR | O_TRUNC | O_CREAT, 0644)) == -1){
                perror("Error with opening of file!\n");
                exit(-1);
        }

        int i = 0;
        write(fd1, &i, sizeof(int));

        int pid = fork();
        if (pid == -1){
                perror("Error with creating of new process!\n");
                exit(-1);
        }

        for (int i = 0; i < 1000; ++i)
        {
                lseek(fd1, 0, SEEK_SET);
                int num;
                read(fd1, &num, sizeof(int));
                lseek(fd1, 0, SEEK_SET);

                if (pid > 0){
                        num++;
                        printf("Parent: %d\n", num);
                }
                else{
                        num += 2;
                        printf("\tChild: %d\n", num);
                }
                write(fd1, &num, sizeof(int));
        }

        close(fd1);        

        return 0;
}
