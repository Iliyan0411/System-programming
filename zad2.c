#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char **argv)
{
    while(true)
    {
        char *text = (char *)calloc(1000, sizeof(char));
        read(0, text, 999);
        text[strlen(text)] = '\0';

        write(1, text, strlen(text));
    }


    return 0;
}