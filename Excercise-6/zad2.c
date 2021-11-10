#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>



int main()
{
        int pid = fork();

        if(pid == -1){
                perror("Error\n");
                exit(-1);
        }
        else if(pid > 0){
                printf("%d\n", getpid());
                printf("%d\n", getppid());
        }
        else{
                fork();
                printf("%d\n", getpid());
                printf("%d\n", getppid());
        }


        return 0;
}
