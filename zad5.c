#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>


int main(int argc, char **argv)
{
    if(argc <= 2) {
        return -1;
    }

    bool c = false, w = false, l = false;

    if(argv[1][0] != '-')
    {
        printf("%s\n", "Wrong command!");
        return -1;
    }

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

    // Must loop over all files...

    return 0;
}