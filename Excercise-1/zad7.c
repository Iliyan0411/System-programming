#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char **argv)
{
        int m, n;
        scanf("%d", &m);
        scanf("%d", &n);

        if(m > n)
        {
                return 0;
        }
        
        int fd;
        if((fd = open(argv[1], O_RDONLY)) == -1){
                exit(-1);
        }

        int size = lseek(fd, 0, SEEK_END);
        lseek(fd, 0, SEEK_SET);
        if(n > size){
                return 0;
        }
        char *text = (char *)calloc(size+1, sizeof(char));
        read(fd, text, size);
        text[size] = '\0';
        --m;
        --n;
        for(int i = 0; i < size; i++)
        {
                if(i >= m && i <= n){
                        printf("%c", text[i]);
                }    
                if(i > n){
                        break;
                }
        }

        return 0;
}
