#include <stdlib.h>
#include <string.h>
#include "fish.h"
#include "debug.h"

/**
 * creates a fish with a given name and frame
 * @param name : name of the fish
 * @param frame : the frame related to the fish
 * @return a pointer to an allocated fish structure, needs to be freed
 */
fish *fish__create(char *name, frame *intial_frame)
{
    fish *f = malloc(sizeof(fish));
    f->is_started = 0;
    f->position = 0;
    f->name = malloc(sizeof(char) * FISH_NAME_MAX_SIZE);
    f->frame = intial_frame;
    strcpy(f->name, name);
    for (int i = 1; i < FISH_PATH_SIZE; i++)
        f->path[i]= NULL;
    return f;
}

/**
 * frees an allocated fish structure
 * @param fish : a pointer to the structre to free
 */
void fish__create_path(fish *f, frame *viewer)
{
    DEBUG_OUT("viewer->width == %d && viewer->height == %d\n", viewer->width, viewer->height);
    f->path[0] = f->frame;
    frame__move_randomly_inside(f->path[0], viewer);
    for (int i = 1; i < FISH_PATH_SIZE; ++i) {
        f->path[i] = malloc(sizeof(frame));
        f->path[i]->width = f->frame->width;
        f->path[i]->height = f->frame->height;
        f->path[i]->y = f->path[i-1]->y;
        f->path[i]->x = f->path[i-1]->x;
        frame__move_randomly_inside(f->path[i], viewer);
    }
}

/**
 * creates a path for the given fish by allocating a randomly filling a table of frames
 * @param f : a pointer to the fish structure
 * @param viewer : a frame representing the aquarium
 */
void fish__free(fish *fish)
{
    free(fish->name);
    free(fish->frame);
    for (int i = 1; i < FISH_PATH_SIZE; i++){
        if (fish->path[i]!= NULL)
            free(fish->path[i]);
    }
    free(fish);
}
