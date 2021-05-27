#ifndef UTILS_H
#define UTILS_H

#include <stdio.h>
#include <stdlib.h>

#define PATH_MAX_SIZE 50

typedef enum status
{
    CONNECTED,
    DISCONNECTED,
} status;

#define ERROR(msg)       \
    do                   \
    {                    \
        perror(msg);     \
        exit(1);         \
    } while (0)

#define EXIT_IF(cond, err) \
    do                     \
    {                      \
        if (cond)          \
        {                  \
            ERROR(err);    \
        }                  \
    } while (0)


void utils__parser(char *parsed_msg[], char *msg, char *sep);
int utils__count_tokens(char *message[]);

#endif //UTILS_H
