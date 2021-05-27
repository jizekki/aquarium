#ifndef VIEW_H
#define VIEW_H

#include <sys/queue.h>
#include "frame.h"

#define VIEW_NAME_MAX_SIZE 5

typedef struct view
{
    char *name;
    frame *frame;
    int taken;
    STAILQ_ENTRY(view)
    next;
} view;

/**
 * creates a view with the given name and frame
 * @param name : a string representing the name of the view
 * @param frame : a frame representing the view coordinates
 * @return : a pointer to an allocated view, needs to be freed
 */
view *view__create(char *name, frame *frame);

/**
 * frees a given view
 * @param view : a pointer to the views that needs to be freed
 */
void view__free(view *view);

#endif //VIEW_H
