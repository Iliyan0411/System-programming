#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{
    int fd2 = open("fff", O_WRONLY | O_CREAT, 0644);
    int fd1 = open("fff", O_RDONLY);
    int fd3 = open("fff", O_RDWR);

    // A)
    // write(fd2, "Hello world!", 12);

    // char *buff = (char *)calloc(7, sizeof(char));
    // read(fd3, buff, 6);
    // printf("%s", buff);
    // free(buff);

    // char *buffer = (char *)calloc(6, sizeof(char));
    // read(fd1, buffer, 5);
    // printf("%s", buffer);
    // free(buffer);

    // write(fd3, "chil", 4);
    // write(fd2, "!!!", 3);

    // char *buf = (char *)calloc(10, sizeof(char));
    // read(fd1, buf, 9);
    // write(1, buf, 9);

    // close(fd1);
    // close(fd2);
    // close(fd3);


    // B)
    // write(fd3, "Hello", 5);
    // write(fd2, "worlds", 6);

    // char *buff1 = (char *)calloc(7, sizeof(char));
    // read(fd1, buff1, 6);
    // write(1, buff1, 6);

    // close(fd2);

    // write(fd3, "oops", 4);

    // char *buff2 = (char *)calloc(7, sizeof(char));
    // read(fd1, buff2, 6);
    // write(1, buff2, 6);

    // close(fd1);
    // close(fd3);

    return 0;
}