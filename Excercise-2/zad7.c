#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>


int main(int argc, char **argv)
{
        for(int i = 5; i >= 1; --i)
        {
              exit(execlp("wc", "wc", "-c", argv[1], (char *)0));
        }


        return 0;
}
