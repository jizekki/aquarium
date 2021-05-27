#ifndef CONNECTION_H
#define CONNECTION_H

#include <sys/queue.h>
#include <pthread.h>
#include "view.h"
#include "utils.h"

#define BUFFER_MAX_SIZE 256

typedef struct connection
{
    int socket_fd;
    char *command_buffer;
    char *answer_buffer;
    view *associated_view;
    status status;
    int timeout;
    pthread_t thread;
    STAILQ_ENTRY(connection)
    next;
} connection;


/**
 * starts a connection to communicate with a client. Should be run on a separate thread
 * @param c : a pointer to the connection to be started
 * @return : NULL
 */
void *connection__start(void *c);

/**
 * ends a connection by closing the socket
 * @param socket_fd : the file descriptor of the socket to close
 */
void connection__end(int socket_fd);

/**
 * frees a connection
 * @param c : a pointer to the connection to free
 */
void connection__free(connection * c);

#endif //CONNECTION_H
