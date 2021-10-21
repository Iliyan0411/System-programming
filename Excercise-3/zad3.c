#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>


int main(int argc, char **argv)
{
    int fd = open(argv[2], O_RDONLY);

    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char *buffer = (char *)calloc(size+1, sizeof(char));
    
    read(fd, buffer, size);
    int count_breaks = 0;
    for(int i = 0; i < size; ++i)
    {
        if(count_breaks >= atoi(argv[1]))
        {
            printf("%c", buffer[i]);
        }
        else
        {
            if(buffer[i] == '\n')
            {
                count_breaks++;
            }
        }
    }

    close(fd);

    return 0;
}