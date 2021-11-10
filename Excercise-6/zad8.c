#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>


int main(int argc, char **argv)
{
       int pid = fork(), status;

       if(pid == -1){
               perror("Error with fork().\n");
               exit(-1);
       }
       else if(pid > 0){
               wait(&status);

               if(status == 0){
                       execlp(argv[2], argv[2], (char *)0);
               }

              exit(-1);
       }
       else{
               execlp(argv[1], argv[1], (char *)0);
       }


        return 0;
}
