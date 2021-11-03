#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <wait.h>


int main(int argc, char **argv)
{
    int pid = fork(), status;

    if(pid == -1){
        perror("Something went wrong with fork() command.\n");
        exit(-1);
    }
    else if(pid > 0){
        int chid = wait(&status);

        if(status >= 0){
            printf("%d\n", chid);
        }
    }
    else{
        char **args = (char **)malloc(argc * sizeof(char));
        for(int i = 0; i < argc-1; ++i)
        {
            args[i] = argv[i+1];
        }
        char end[5] = "NULL";
        args[argc] = end;

        execvp(argv[1], args);
    }


    return 0;
}