#ifndef SERVER_H
#define SERVER_H

#include "utils.h"

typedef struct server {
    int port;
    int timeout;
    int fish_update_interval;
    status status;
    aquarium *aquarium;
    STAILQ_HEAD(, connection)
            connections_list;

}server;

/**
 * launches a server by responding to requests
 * @param server : a pointer to the server to launch
 */
void server__launch(server *server);

/**
 * updates the positions of the fish in the aquarium if they are started
 * @param args : not used (can be NULL)
 * @return : NULL
 */
void *server__update(void *args);

/**
 * gets and responds the commands from the controller's console
 * @param args : not used (can be NULL)
 * @return : NULL
 */
void *server__interface(void *args);

#endif //SERVER_H
