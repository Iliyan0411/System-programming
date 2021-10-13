#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>



int main(int argc, char **argv)
{
        int fd = open(argv[1], O_RDWR|O_CREAT|O_TRUNC, 0644);
        if(fd < 0)
        {
                close(fd);
                exit(-1);
        }

        char *buffer = (char *)calloc(27, sizeof(char));
        for(int i = 0; i < 26; i++)
        {
                buffer[i] = 'a' + i;
        }
        buffer[26] = '\0';

        write(fd, buffer, 26);
        free(buffer);

        char *buff = (char *)calloc(11, sizeof(char));
        int len;
        while((len = read(fd, buff, 10)) > 0)
        {
                printf("%d\n", len);
                /*buff[10] = '\0';*/
                /*printf("%s", buff);*/
        }

        close(fd);

        return 0;
}
