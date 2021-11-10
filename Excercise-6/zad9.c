#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>

int main(int argc, char **argv)
{
        int printed = 0;
        int pid = fork();

        if (pid == -1){
                perror("Error.\n");
                exit(-1);
        }
        else if (pid > 0){
                int pid1 = fork();

                if (pid1 == -1){
                        perror("Error.\n");
                        exit(-1);
                }
                else if (pid1 > 0){
                        int status;
                        int child = wait(&status);

                        if (printed == 0){
                                printed++;
                                printf("%d\n", child);
                                return 0;
                        }
                }
                else{
                        if (printed == 0) execlp(argv[1], argv[1], (char *)0);
                }
        }
        else{
                int pid2 = fork();

                if (pid2 == -1){
                        perror("Error.\n");
                        exit(-1);
                }
                else if (pid2 > 0){
                        int status;
                        int child = wait(&status);

                        if (printed == 0){
                                printed++;
                                printf("%d\n", child);
                                return 0;
                        }
                }
                else{
                        if (printed == 0) execlp(argv[2], argv[2], (char *)0);
                }
        }

        return 0;
}
