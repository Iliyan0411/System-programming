#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd = open(argv[1], O_RDWR | O_TRUNC | O_CREAT, 0644);
    int pid = fork(), status;

    if (pid == -1)
    {
        perror("Something went wrong!\n");
        exit(-1);
    }
    else if (pid > 0)
    {
        wait(&status);

        int size = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);
        char *text = (char *)calloc(size + 1, sizeof(char));

        read(fd, text, size);
        for (int i = 0; i < size; ++i)
        {
            char *buffer = (char *)calloc(3, sizeof(char));
            buffer[0] = text[i];
            buffer[1] = ' ';
            buffer[2] = '\0';

            write(1, buffer, 2);
            if (i < size - 1)
                write(1, " ", 1);

            free(buffer);
        }

        free(text);
    }
    else
    {
        write(fd, "Hello", 5);
    }

    return 0;
}