#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    if(argc != 3)
    {
        return -1;
    }

    int fd[2];
    fd[0] = open(argv[1], O_RDONLY);
    fd[1] = open(argv[2], O_WRONLY | O_CREAT, 0744);

    int size = lseek(fd[0], 0, SEEK_END);
    lseek(fd[0], 0, SEEK_SET);

    char *text = (char *)calloc(size+1, sizeof(char));
    read(fd[0], text, size);
    text[size] = '\0';

    write(fd[1], text, size);

    close(fd[0]);
    close(fd[1]);


    return 0;
}