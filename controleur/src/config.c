#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "config.h"
#include "utils.h"

#define BUFFER_SIZE 100
#define CONFIG_PATH "controller.cfg"

int port = -1;
int timeout_value = -1;
int fish_update = -1;

void config__parser(FILE *config_file)
{
    char buffer[BUFFER_SIZE];
    char *tokens[10];
    int config_value;

    while (!feof(config_file))
    {
        fgets(buffer, BUFFER_SIZE, config_file);
        utils__parser(tokens, buffer, " = ");
        if (tokens[0] != NULL && tokens[1] != NULL)
        {
            config_value = atoi(tokens[1]);
            if (!strcmp(tokens[0], "controller-port"))
                port = config_value;

            else if (!strcmp(tokens[0], "display-timeout-value"))
                timeout_value = config_value;

            else if (!strcmp(tokens[0], "fish-update-interval"))
                fish_update = config_value;
        }
    }
}

void config__init()
{
    FILE *file;
    file = fopen(CONFIG_PATH, "r");
    if (file != NULL)
    {
        config__parser(file);
        fclose(file);
    }
    else {
        ERROR("Impossible d'ouvrir le fichier de configuration ( contoleur/controller.cfg )\n");
    }
}

int config__get_port()
{
    if (port == -1)
    {
        ERROR("Numero de port requis dans le fichier de configuration ( contoleur/controller.cfg )\
        \nUsage\n \
        controller-port = <numero de port> \n \
        display-timeout-value = <duree (s)>\n \
        fish-update-interval =  <duree (s)>\n");
    }
    return port;
}

int config__get_timeout()
{
    if (timeout_value == -1)
    {
        ERROR("Timeout requis dans le fichier de configuration ( contoleur/controller.cfg )\
        \nUsage\n \
        controller-port = <numero de port> \n \
        display-timeout-value = <duree (s)>\n \
        fish-update-interval =  <duree (s)>\n");
    }
    return timeout_value;
}

int config__get_fish_interval()
{
    if (fish_update == -1)
    {
        ERROR("Fish update interval requis dans le fichier de configuration ( contoleur/controller.cfg )\
        \nUsage\n \
        controller-port = <numero de port> \n \
        display-timeout-value = <duree (s)>\n \
        fish-update-interval =  <duree (s)>\n");
    }
    return fish_update;
}
