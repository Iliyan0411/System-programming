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
        if (str[i] != ' ' && str[i] != '\t'){
            inWord = true;
            cleanedStr[j++] = str[i];
        }
        else{
            if (inWord){
                cleanedStr[j++] = ' ';
                inWord = false;
            }
        }
    }
    cleanedStr[--j] = '\0';

    return cleanedStr;
}

char **split(const char *str, int *j)
{
    char **args = (char **)calloc(200, sizeof(char));

    for (int i = 0; i < strlen(str); i++)
    {
        char *buffer = (char *)calloc(200, sizeof(char));
        int k = 0;

        while (i < strlen(str) && str[i] != ' ')
        {
            buffer[k++] = str[i++];
        }

        if (k > 0){
            int temp = *j;
            args[temp++] = buffer;
            *j = temp;
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

bool hasVerticalLine(char **commands, int numberOfCommands)
{
    for (int i = 0; i < numberOfCommands; ++i)
    {
        if (!strcmp(commands[i], "|")){
            return true;
        }
    }

    return false;
}

char **getHalfArgs(char **commands, int numberOfCommands, bool leftArgs)
{
    char **args = (char **)malloc(100 * sizeof(char));

    if (leftArgs){
        int i = 0;
        while (strcmp(commands[i], "|"))
        {
            args[i] = commands[i];
            i++;
        }
    }
    else{
        bool finded = false;
        int j = 0;

        for (int i = 0; i < numberOfCommands; ++i)
        {
            if (finded){
                args[j++] = commands[i];
            }

            if (!strcmp(commands[i], "|")){
                finded = true;
            }
        }
    }

    return args;
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

        int numberOfCommands = 0;
        char **commands = split(temp, &numberOfCommands);

        if (!strcmp(temp, "bye")){
            free(command);
            free(temp);
            clearMemory(commands);

            write(1, "See you again.\n", 15);

            return 0;
        }
        free(temp);

        if (hasVerticalLine(commands, numberOfCommands)){
            char **leftArgs = getHalfArgs(commands, numberOfCommands, true);
            char **rightArgs = getHalfArgs(commands, numberOfCommands, false);

            int pid1 = fork();

            if (pid1 < 0){
                write(1, "Fork error", 10);
            }
            else if (pid1 > 0){
                int status1;
                wait(&status1);

                if (status1 != 0){
                    write(1, "Error with command execution!\n", 30);
                }
            }
            else{
                int fd[2];
                if (pipe(fd) == -1){
                    write(1, "Pipe error!\n", 12);
                }

                int pid2 = fork();

                if (pid2 < 0){
                    write(1, "Fork error", 10);
                }
                else if (pid2 > 0){
                    int status2;
                    wait(&status2);

                    close(0);
                    dup(fd[0]);
                    close(fd[0]);
                    close(fd[1]);

                    exit(execvp(rightArgs[0], rightArgs));
                }
                else{
                    close(1);
                    dup(fd[1]);
                    close(fd[0]);
                    close(fd[1]);

                    exit(execvp(leftArgs[0], leftArgs));
                }
            }

            free(command);
            clearMemory(commands);
        }
        else if (command[0] != '\n'){
            int pid = fork();

            if (pid < 0){
                write(1, "Error with fork() command!\n", 27);
            }
            else if (pid > 0){
                int status;
                wait(&status);

                free(command);
                clearMemory(commands);

                if (status != 0){
                    write(1, "Error with command execution!\n", 30);
                }
            }
            else{
                exit(execvp(commands[0], commands));
            }
        }
        else{
            free(command);
        }
    }

    return 0;
}
