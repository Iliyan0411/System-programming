#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char **argv)
{
    if(argc == 1) {
        return -1;
    }

    while(true)
    {
        char *text = (char *)calloc(1000, sizeof(char));
        read(0, text, 999);
        text[strlen(text)] = '\0';

        for(int i = 1; i < argc; ++i)
        {
            int fd = open(argv[i], O_WRONLY | O_CREAT | O_APPEND, 0644);

            write(fd, text, strlen(text));

            close(fd);
        }

        free(text);
    }


    return 0;
}