#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <string.h>
#include <stdbool.h>

char *clearWhitespaces(const char *str)
{
    int j = 0;
    bool inWord = false;
    char *cleanedStr = (char *)calloc(512, sizeof(char));

    for (int i = 0; i < strlen(str); ++i)
    {
        if(str[i] != ' ' && str[i] != '\t'){
            inWord = true;
            cleanedStr[j++] = str[i];
        }
        else{
            if(inWord){
                cleanedStr[j++] = ' ';
                inWord = false;
            }
        }
    }
    cleanedStr[--j] = '\0';

    return cleanedStr;
}

char **split(const char *str)
{
    char **args = (char **)calloc(200, sizeof(char));
    int j = 0, i = 0;

    for (int i = 0; i < strlen(str); i++)
    {
        char *buffer = (char *)calloc(200, sizeof(char));
        int k = 0;

        while (i < strlen(str) && str[i] != ' ')
        {
            buffer[k++] = str[i++];
        }

        if (k > 0){
            args[j++] = buffer;
        }
    }

    return args;
}

void clearMemory(char **str)
{
    for (int i = 0; i < strlen(*str); ++i)
    {
        free(str[i]);
    }
    free(str);
}


int main(int argc, char **argv)
{
    while (1)
    {
        write(1, "\033[0;31m", 7);
        write(1, "prompt> ", 8);
        write(1, "\033[0m", 4);

        char *command = (char *)calloc(512, sizeof(char));
        read(0, command, 510);

        char *temp = (char *)calloc(512, sizeof(char));
        temp = clearWhitespaces(command);

        char **commands = (char **)calloc(70, sizeof(char));
        commands = split(temp);

        if (!strcmp(temp, "bye")){
            free(command);
            free(temp);
            clearMemory(commands);

            write(1, "See you again.\n", 15);

            return 0;
        }
        free(temp);

        if (command[0] != '\n'){
            int pid = fork();
            bool error = false;

            if (pid < 0){
                write(1, "Error with fork() command!\n", 27);
                error = true;
            }
            else if (pid > 0){
                int status;
                wait(&status);

                free(command);
                clearMemory(commands);

                if (status != 0)
                {
                    write(1, "Error with command execution!\n", 30);
                }
            }
            else{
                if (!error){
                    exit(execvp(commands[0], commands));
                }
                exit(-1);
            }
        }
        else{
            free(command);
        }
    }

    return 0;
}