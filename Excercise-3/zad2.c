#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{
    int fd1 = open("f1", O_RDWR);
    int fd2 = open("f1", O_RDWR);

    int size = lseek(fd1, -2, SEEK_END) + 2;
    write(fd1, "wxyz", 4);

    lseek(fd1, 4, SEEK_SET);
    write(fd1, "12", 2);

    char *buffer = (char *)calloc(size+1, sizeof(char));
    read(fd2, buffer, size);

    write(1, buffer, size);

    close(fd1);
    close(fd2);

    return 0;
}