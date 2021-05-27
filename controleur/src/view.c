#include <string.h>
#include <stdlib.h>
#include "view.h"

/**
 * creates a view with the given name and frame
 * @param name : a string representing the name of the view
 * @param frame : a frame representing the view coordinates
 * @return : a pointer to an allocated view, needs to be freed
 */
view *view__create(char *name, frame *frame)
{
    view *v = malloc(sizeof(view));
    v->name= (char*)malloc(sizeof(char) *30);
    strcpy(v->name, name);
    v->frame = frame;
    v->taken = 0;
    return v;
}

/**
 * frees a given view
 * @param view : a pointer to the view that needs to be freed
 */
void view__free(view *view)
{
    free(view->name);
    free(view->frame);
    free(view);
}
