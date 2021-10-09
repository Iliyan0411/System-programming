#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDONLY);

    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char *text = (char *)calloc(size+1, sizeof(char));
    read(fd, text, size);
    text[size] = '\0';

    close(fd);

    int breaks = 1;
    for(int i = 0; i < size; ++i)
    {
        if(text[i] == '\n'){
            breaks++;
        }
        if(breaks > 10){
            break;
        }
        printf("%c", text[i]);
    }

    free(text);

    return 0;
}
