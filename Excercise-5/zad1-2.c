#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>


int main(int argc, char **argv)
{
    execlp("grep", "grep", "int", argv[1], (char *)0);


    return 0;
}