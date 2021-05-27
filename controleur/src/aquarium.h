#ifndef AQUARIUM_H
#define AQUARIUM_H

#include <stdio.h>
#include <stdlib.h>
#include <sys/queue.h>
#include "view.h"
#include "frame.h"
#include "fish.h"

#define AQUARIUM__DEFAULT_FRAME "0x0+1000+1000"

typedef struct aquarium
{
    frame *frame;
    STAILQ_HEAD(, fish)
    fish_list;
    STAILQ_HEAD(, view)
    views_list;
} aquarium;

/**
 * creates an empty aquarium
 * @return a pointer to an allocated aquarium structure, needs to be freed
 */
aquarium *aquarium__empty();

/**
 * fills an aquarium with data the given file
 * @param aq : a pointer to the aquarium to fill
 * @param f : a file descriptor from which data should be imported
 */
void aquarium__load(aquarium *aq, FILE *f);

/**
 * saves an aquarium's data to a file
 * @param aq : a pointer to the aquarium
 * @param filename : the name of the file where to save data
 */
void aquarium__save(const aquarium *aq, const char *filename);

/**
 * adds a fish to an aquarium's fish list
 * @param aq : a pointer to the aquarium
 * @param f : a pointer to the fish to add
 * @return : 0 if the fish is added and -1 if not
 */
int aquarium__add_fish(aquarium *aq, fish *f);

/**
 * removes a fish from an aquarium's fish list
 * @param aq : a pointer to the aquarium
 * @param f : a string indicating the name of the fish to remove
 * @return : 0 if the fish is removed and -1 if not
 */
int aquarium__del_fish(aquarium *aq, const char *name);

/**
 * adds a view to an aquarium's views list
 * @param aq : a pointer to the aquarium
 * @param f : a pointer to the view to add
 * @return : 0 if the view is added and -1 if not
 */
int aquarium__add_view(aquarium *aq, view *v);

/**
 * removes a view from an aquarium's views list
 * @param aq : a pointer to the aquarium
 * @param f : a string indicating the name of the view to remove
 * @return : 0 if the view is removed and -1 if not
 */
int aquarium__del_view(aquarium *aq, const char *name);

/**
 * counts the number of views in an aquarium
 * @param aq : a pointer to the aquarium
 * @return : the number of views in the aquarium
 */
int aquarium__count_views(const aquarium *aq);

/**
 * returns a pointer to a view from the aquarium not taken by any client
 * @param aq : a pointer to the aquarium
 * @return : a pointer to a view or NULL if no view is available
 */
view *aquarium__get_free_view(const aquarium *aq);

/**
 * returns a pointer to the view specified by name from the aquarium
 * @param aq : a pointer to the aquarium
 * @param name : the name of the view
 * @return a pointer to a view or NULL if no view is found
 */
view *aquarium__get_view(const aquarium *aq, const char *name);

/**
 * returns a pointer to the fish specified by name from the aquarium
 * @param aq : a pointer to the aquarium
 * @param name : the name of the fish
 * @return a pointer to a fish or NULL if no view is found
 */
fish *aquarium__get_fish(const aquarium *aq, const char *name);

/**
 * returns the number of fish included in a view
 * @param aq : a pointer to the aquarium
 * @param v : a pointer to the view
 * @return : the number of fish in the view
 */
int aquarium__count_fish_in_view(const aquarium *aq, const view *v);

/**
 * frees the memory allocated for an aquarium
 * @param aq : a pointer to the aquarium
 */
void aquarium__free(aquarium *aq);

#endif //AQUARIUM_H
