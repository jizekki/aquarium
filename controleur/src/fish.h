#ifndef FISH_H
#define FISH_H

#include <sys/queue.h>
#include "frame.h"

#define FISH_NAME_MAX_SIZE 30
#define FISH_PATH_SIZE 1000

typedef struct fish
{
    char *name;
    frame *frame;
    int is_started;
    int position;
    frame *path[FISH_PATH_SIZE];
    STAILQ_ENTRY(fish)
    next;
} fish;

/**
 * creates a fish with a given name and frame
 * @param name : name of the fish
 * @param frame : the frame related to the fish
 * @return a pointer to an allocated fish structure, needs to be freed
 */
fish *fish__create(char *name, frame *frame);

/**
 * frees an allocated fish structure
 * @param fish : a pointer to the structre to free
 */
void fish__free(fish *fish);

/**
 * creates a path for the given fish by allocating a randomly filling a table of frames
 * @param f : a pointer to the fish structure
 * @param viewer : a frame representing the aquarium
 */
void fish__create_path(fish *f, frame *viewer);

#endif //FISH_H
