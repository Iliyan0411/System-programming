#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <wait.h>
#include <string.h>

char *clearWhitespaces(const char *str)
{
    int j = 0;
    char *cleanedStr = (char *)calloc(512, sizeof(char));

    for (int i = 0; i < strlen(str); ++i)
    {
        if (j == 0){
            if (str[i] != ' ' && str[i] != '\t'){
                cleanedStr[j++] = str[i];
            }
        }
        else{
            cleanedStr[j++] = str[i];
        }
    }

    if (cleanedStr != NULL){
        for (int i = strlen(cleanedStr) - 1; i >= 0; --i)
        {
            if (cleanedStr[i] != ' ' && cleanedStr[i] != '\t'){
                cleanedStr[i] = '\0';
                break;
            }
        }
    }

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
        write(1, "\033[0;31m", 7); // Red color of a text
        write(1, "prompt> ", 8);
        write(1, "\033[0m", 4); // Reset default color

        char *command = (char *)calloc(512, sizeof(char));
        read(0, command, 510); // Reading commands

        char *temp = (char *)calloc(512, sizeof(char));
        strcpy(temp, clearWhitespaces(command));

        char **commands = (char **)calloc(70, sizeof(char));
        commands = split(temp);

        if (strlen(temp) == 3 && temp[0] == 'b' && temp[1] == 'y' && temp[2] == 'e'){
            free(command);
            free(temp);
            clearMemory(commands);

            write(1, "See you again.\n", 15);

            return 0;
        }
        free(temp);

        if (command[0] != '\n'){
            int pid = fork(), error = 0, status = 0;

            if (pid < 0){
                write(1, "Error with fork() command!\n", 27);
                error = 1;
            }
            else if (pid > 0){
                wait(&status);

                free(command);
                clearMemory(commands);

                if (status != 0)
                {
                    write(1, "Error with command execution!\n", 30);
                }
            }
            else{
                if (error == 0){
                    execvp(commands[0], commands);
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