#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    if(argc != 2)
    {
        return -1;
    }

    int fd;
    if((fd = open(argv[1], O_WRONLY | O_CREAT, 0644)) == -1)
    {
        perror("An error has occured!\n");
        return -1;
    }

    close(1);
    dup(fd);

    for(int i = 0; i < 10; ++i)
    {
        write(1, "EXAMPLE", 8);
    }

    close(fd);

    return 0;
}