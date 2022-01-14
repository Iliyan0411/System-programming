#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <wait.h>


int main(int argc, char **argv)
{
    if(argc < 3){
        write(1, "Wrong number of arguments!\n", 27);
        exit(-1);
    }

   int pid1, pid2, pid3;

   if((pid1 = fork()) == -1){
       write(1, "Error with first fork!\n", 23);
       exit(-1);
   }
   else if(pid1 > 0){
       int status1;
       int childID = wait(&status1);

       if(status1 == 0){
           printf("%d\n", childID);
       }
   }
   else{
       if((pid2 = fork()) == -1){
            write(1, "Error with first fork!\n", 23);
            exit(-1);
       }
       else if(pid2 > 0){
           int status2;
           int childID = wait(&status2);

            if(status2 == 0){
                printf("%d\n", childID);
            }

           char **args = (char **)malloc(100 * sizeof(char));
           for(int i = 0; i < argc-2; ++i)
           {
               args[i] = argv[i+2];
           }

           exit(execvp(args[0], args));
       }
       else{
           if((pid3 = fork()) == -1){
                write(1, "Error with first fork!\n", 23);
                exit(-1);
           }
           else if(pid3 > 0){
               int status3;
               int childID = wait(&status3);

                if(status3 == 0){
                    printf("%d\n", childID);
                }

               exit(execlp("ls", "ls", "-l", "/home/iliyan/Iliyan", (char *)0));
           }
           else{
               exit(execlp("cp", "cp", argv[1], "f1", (char *)0));
           }
       }
   }


    return 0;
}