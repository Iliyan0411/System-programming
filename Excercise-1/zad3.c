#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char **argv)
{
    if(argc != 2)
    {
        return -1;
    }

    while(true)
    {
        char *text = (char *)calloc(1000, sizeof(char));
        read(0, text, 999);
        text[strlen(text)] = '\0';

        int fd = open(argv[1], O_WRONLY | O_CREAT | O_APPEND, 0644);

        write(fd, text, strlen(text));
        free(text);

        close(fd);
    }
}