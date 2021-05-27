#ifndef COMMAND_H
#define COMMAND_H

#include "connection.h"
#include "aquarium.h"

#define COMMAND__MAX_SIZE 128

/**
 * handles a command received from the controller's console
 * @param cmd : a pointer to the string containing the command to treat
 * @param answer : a pointer to the buffer where the answer should be written
 * @param aq : a pointer to the aquarium
 */
void command__from_server(char *cmd, char *answer, aquarium *aq);
/**
 * handles a command received from the client's prompt
 * @param c : a pointer to the connection (the client)
 * @param aq : a pointer to the aquarium
 */
void command__from_client(connection *c, aquarium *aq);

/**
 * a function to responde to the command 'getFishesContinuously'. Sould be run on a separate thread
 * @param connection : a pointer to the connection (the client)
 * @return : NULL
 */
void *connection__get_fish_continuously(void *connection);

#endif //COMMAND_H
