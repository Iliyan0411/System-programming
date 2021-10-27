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

    for(int i = 0; i < 10; ++i)
    {
        write(1, "EXAMPLE", 8);
    }

    int temp_1 = dup(1);
    close(1);
    int temp_fd = dup(fd);

    write(1, "12345678910", 12);

    close(fd);
    dup(temp_1);

    for(int i = 0; i < 10; ++i)
    {
        write(temp_1, "HELLO", 5);
    }


    return 0;
}