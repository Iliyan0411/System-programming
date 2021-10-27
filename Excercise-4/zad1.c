#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main()
{
    int fd1 = open("f", O_RDONLY);

    int fd2 = dup(fd1);

    char *c1 = (char *)calloc(2, sizeof(char));
    char *c2 = (char *)calloc(2, sizeof(char));
    read(fd1, c1, 1);
    read(fd2, c2, 1);

    printf("%s\n", c1);
    printf("%s\n", c2);

    free(c1);
    free(c2);
    close(fd1);

    int curr_temp = lseek(fd2, 0, SEEK_CUR);
    int end_temp = lseek(fd2, 0, SEEK_END);
    lseek(fd2, curr_temp, SEEK_SET);

    int size = end_temp - curr_temp + 1;
    char *s = (char *)calloc(size+1, sizeof(char));
    read(fd2, s, size);

    write(1, s, size);

    free(s);
    close(fd2);


    return 0;
}