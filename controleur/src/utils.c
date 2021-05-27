#include <string.h>
#include "utils.h"

void utils__parser(char *parsed_message[], char *message, char *separator)
{
    message[strlen(message) - 1] = ' ';
    char *token = strtok(message, separator);
    if (token != NULL)
    {
        parsed_message[0] = token;
        int args = 1;
        while (token != NULL)
        {
            token = strtok(NULL, separator);
            parsed_message[args++] = token;
        }
        parsed_message[args] = NULL;
    }
}

int utils__count_tokens(char *message[])
{
    int i = 0;
    while (message[i] != NULL)
    {
        i++;
    }
    return i;
}
