#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char **argv)
{
        int fd = open(argv[1], O_RDONLY);

        for(int i = 8 ; i >= 1; i--)
        {
                char *buffer = (char *)calloc(16, sizeof(char));
                lseek(fd, -3, SEEK_END);
                read(fd, buffer, 16);
                write(1, buffer, strlen(buffer));
                free(buffer);
        }

        close(fd);


        return 0;
}
