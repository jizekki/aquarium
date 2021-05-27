#include <unistd.h>
#include <strings.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include "connection.h"
#include "utils.h"
#include "command.h"
#include "server.h"
#include "debug.h"

extern server *controller;

/**
 * starts a connection to communicate with a client. Should be run on a separate thread
 * @param c : a pointer to the connection to be started
 * @return : NULL
 */
void *connection__start(void *c)
{
    connection *conn = (connection *)c;
    char answer_buffer[BUFFER_MAX_SIZE];
    conn->answer_buffer = answer_buffer;
    conn->associated_view = NULL;

    fd_set read_fds;
    struct timeval time_out;
    FD_ZERO(&read_fds);
    FD_SET(conn->socket_fd, &read_fds);
    time_out.tv_sec = 5;
    time_out.tv_usec = 0;

    while (conn->status == CONNECTED && controller->status == CONNECTED)
    {
        time_out.tv_sec = conn->timeout;
        time_out.tv_usec = 0;
        int a = select(FD_SETSIZE, &read_fds, NULL, NULL, &time_out);
        if (a == 0)
        {
            conn->status = DISCONNECTED;
            break;
        }

        bzero(conn->command_buffer, BUFFER_MAX_SIZE);
        bzero(conn->answer_buffer, BUFFER_MAX_SIZE);

        ssize_t err = read(conn->socket_fd, conn->command_buffer, BUFFER_MAX_SIZE - 1);
        EXIT_IF(err < 0, "error on read()");
        command__from_client(conn, controller->aquarium);
        signal(SIGPIPE, connection__end);
        err = write(conn->socket_fd, conn->answer_buffer, strlen(conn->answer_buffer));
        EXIT_IF(err < 0, "error on write()");
    }
    DEBUG_OUT("connection ended, proceeding to free\n");
    connection__free(conn);
    DEBUG_OUT("connection freed, thread will now exit\n");
    pthread_exit(NULL);
}

/**
 * ends a connection by closing the socket
 * @param socket_fd : the file descriptor of the socket to close
 */
void connection__end(int socket_fd)
{
    close(socket_fd);
}

/**
 * frees a connection
 * @param c : a pointer to the connection to free
 */
void connection__free(connection * c)
{
    if (c->associated_view != NULL){
        c->associated_view->taken = 0;
    }
    free(c);
}
