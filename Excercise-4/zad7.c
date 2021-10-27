#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
    if(argc != 3)
    {
        return -1;
    }
    
    int fd1, fd2;
    if((fd1 = open(argv[1], O_RDONLY)) == -1)
    {
        perror("An error has occured!\n");
        return -1;
    }

    close(0);
    dup(fd1);

    if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1)
    {
        perror("An error has occured!\n");
        return -1;
    }

    close(1);
    dup(fd2);

    int size = lseek(fd1, 0, SEEK_END);
    lseek(fd1, 0, SEEK_SET);

    char *text = (char *)malloc(sizeof(char) * size+1);
    read(0, text, size);

    write(1, text, size);

    close(fd1);
    close(fd2);

    return 0;
}