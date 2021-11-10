#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int main(int argc, char *argv[])
{
      int fd, j, nb1;
      char buf[5];
      if (fork())
      {
            int status;
            wait(&status);
            execlp("cat", "cat", "fileA.txt", (char *)0);
      }
      else
      {
            // printf("%s\n", "Here1");
            j = dup(1);
            fd = open(argv[1], O_RDWR);
            nb1 = read(0, buf, 5);
            // printf("%d\n", nb1);
            write(j, buf, nb1);
            nb1 = read(fd, buf, 5);
            write(1, buf, nb1);
            write(fd, "\n", 1);
            write(fd, buf, nb1);
            write(j, buf, 3);
            close(fd);
            close(j);
            exit(0);
      }
}

// fileA.txt->0123456789