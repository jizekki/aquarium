#ifndef DEBUG_H
#define DEBUG_H
#include <stdio.h>

#define DEBUG 0
#if DEBUG
#define DEBUG_OUT(...)                         \
    do                                         \
    {                                          \
        fprintf(stderr, "DEBUG: "__VA_ARGS__); \
    } while (0)
#else
#define DEBUG_OUT(...)
#endif //DEBUG

#endif //DEBUG_H
