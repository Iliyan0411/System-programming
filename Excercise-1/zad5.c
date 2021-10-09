#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


int c_option(char *fileName)
{
    int fd = open(fileName, O_RDONLY);
    int size = lseek(fd, 0, SEEK_END);
    close(fd);

    return size;
}

bool isAlpha(char c)
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z');
}

int w_option(char *fileName)
{
    int fd = open(fileName, O_RDONLY);

    int words = 0;
    int size = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    char *text = (char *)calloc(size+1, sizeof(char));
    read(fd, text, size);
    text[size] = '\0';

    for(int i = 0; i < size; ++i)
    {
        if(isAlpha(text[i]) && (i == size-1 || !isAlpha(text[i+1])))
        {
            words++;
        }
    }

    free(text);
    close(fd);

    return words;
}

int l_option(char *fileName)
{
    int lines = 1;

    int fd = open(fileName, O_RDONLY);

    int size = lseek(fd, 0, SEEK_END);
    if(size == 0)
    {
        return 0;
    }

    lseek(fd, 0, SEEK_SET);
    char *text = (char *)calloc(size+1, sizeof(char));
    read(fd, text, size);
    text[size] = '\0';

    close(fd);

    for(int i = 0; i < size; ++i)
    {
        if(text[i] == '\n')
        {
            lines++;
        }
    }
    free(text);

    return lines;
}

int main(int argc, char **argv)
{
    if(argc <= 2) {
        return -1;
    }

    bool c = false, w = false, l = false;

    for(int i = 1; i < strlen(argv[1]); i++) 
    {   
        if(argv[1][i] == 'c'){
            c = true;
        }
        else if(argv[1][i] == 'w'){
            w = true;
        }
        else if(argv[1][i] == 'l'){
            l = true;
        }
        else{
            printf("%s\n", "Wrong command!");
            return -1;
        }
    }

    for(int i = 2; i < argc; ++i)
    {
        if(c == true)
        {
            printf("%s%d ", "c:", c_option(argv[i]));
        }
        if(w == true)
        {
            printf("%s%d ", "w:", w_option(argv[i]));
        }
        if(l == true)
        {
            printf("%s%d ", "l:", l_option(argv[i]));
        }

        printf("%s\n", argv[i]);
    }

    return 0;
}