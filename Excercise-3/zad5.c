#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>


int main(int argc, char **argv)
{
        int fd1;
        if((fd1 = open(argv[1], O_RDONLY)) == -1)
        {
                printf("%s\n", "An error has occured!");
                return -1;
        }

        int size = lseek(fd1, 0, SEEK_END);
        lseek(fd1, 0, SEEK_SET);

        char *text = (char *)calloc(size+1, sizeof(char));
        read(fd1, text, size);

        int i = 0, j = 0, newLines = 0;
        while(i < size)
        {
                char *line = (char *)calloc(61, sizeof(char));
                while(i < size && text[i] != '\n')
                {
                        line[j++] = text[i++];
                }
                line[j] = '\0';
                if(line[j-1] == '$')
                {
                        write(1, line, j);
                        printf("%c", '\n');
                }
                else
                {
                        int fd2;
                        if((fd2 = open(argv[2], O_WRONLY | O_CREAT | O_APPEND, 0644)) == -1)
                        {
                                printf("%s\n", "An error has occured!");
                                return -1;
                        }

                        char *digits = (char *)calloc(j, sizeof(char));
                        int pos = 0;
                        for(int k = 0; k < j; ++k)
                        {
                                if(line[k] >= '0' && line[k] <= '9')
                                {
                                        digits[pos++] = line[k];
                                }
                        }
                        digits[pos++] = '\n';
                        digits[pos] = '\0';
                        write(fd2, digits, pos);
                        newLines++;

                        free(digits);
                        close(fd2);
                }
                j = 0;
                i++;
                free(line);
        }

        printf("%d\n", newLines);

        close(fd1);
        free(text);


        return 0;
}
