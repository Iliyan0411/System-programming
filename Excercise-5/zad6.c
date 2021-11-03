#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>


int main(int argc, char **argv)
{
    int pid, status;
    
    for(int i = 0; i < 3; ++i)
    {
        pid = fork();

        if(pid == -1){
            perror("Somerhing went wrong.\n");
            exit(-1);
        }
        else if(pid > 0){
            int chid = wait(&status);

            write(1, "Procces ID <-> Status: ", 24);
            printf("%d <-> %d\n\n", chid, status);
        }
        else{
            execlp(argv[i+1], argv[i+1], (char *)0);
        }
    }


    return 0;
}