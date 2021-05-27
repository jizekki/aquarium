#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "command.h"
#include "utils.h"
#include "config.h"
#include "server.h"
#include "debug.h"
#include "frame.h"

extern server *controller;

/**
 * handles a command received from the controller's console
 * @param cmd : a pointer to the string containing the command to treat
 * @param answer : a pointer to the buffer where the answer should be written
 * @param aq : a pointer to the aquarium
 */
void command__from_client(connection *c, aquarium *aq)
{
	char *tmp_buffer = malloc(sizeof(char) * COMMAND__MAX_SIZE);
	strcpy(tmp_buffer, c->command_buffer);
	char *parsed_command[COMMAND__MAX_SIZE];
	utils__parser(parsed_command, c->command_buffer, " ");
	int tokens_len = utils__count_tokens(parsed_command);

	if (tokens_len == 2 && !strcmp(parsed_command[0], "ping"))
	{
		if (atoi(parsed_command[1]) == config__get_port())
		{
			sprintf(c->answer_buffer, "pong %d\n", config__get_port());
		}
		else
		{
			sprintf(c->answer_buffer, "NOK\n");
		}
	}
	else if (tokens_len == 1 && !strcmp(parsed_command[0], "getFishes"))
	{
		fish *f;
        sprintf(c->answer_buffer, "list ");
        STAILQ_FOREACH(f, &(controller->aquarium->fish_list), next)
        {
            if (frame__includes_snippet(c->associated_view->frame, f->frame))
            {
                frame *relative_frame = frame__get_relative(f->frame, c->associated_view->frame);
                sprintf(c->answer_buffer, "%s [%s at %dx%d,%dx%d,%d]", c->answer_buffer, f->name, relative_frame->x, relative_frame->y,relative_frame->width, relative_frame->height, 5);
                free(relative_frame);
            }
        }
        sprintf(c->answer_buffer, "%s\n", c->answer_buffer);
	}
	else if (tokens_len == 1 && !strcmp(parsed_command[0], "hello"))
	{
		if(c->associated_view == NULL) {
            c->associated_view = aquarium__get_free_view(aq);
            if (c->associated_view)
            {
                c->associated_view->taken = 1;
                sprintf(c->answer_buffer, "greeting %s\n", c->associated_view->name);
            }
            else
            {
                sprintf(c->answer_buffer, "no greeting\n");
                c->status = DISCONNECTED;
            }
		} else
        {
            sprintf(c->answer_buffer, "OK\n");
        }
	}
	else if (tokens_len == 4 && !strcmp(parsed_command[0], "hello") && !strcmp(parsed_command[1], "in") && !strcmp(parsed_command[2], "as"))
	{
        if (c->associated_view == NULL) {
            c->associated_view = aquarium__get_view(aq, parsed_command[3]);
            if (c->associated_view && c->associated_view->taken == 0)
            {
                c->associated_view->taken = 1;
                sprintf(c->answer_buffer, "greeting %s\n", c->associated_view->name);
            }
            else
            {
                c->associated_view = aquarium__get_free_view(aq);
                if (c->associated_view)
                {
                    c->associated_view->taken = 1;
                    sprintf(c->answer_buffer, "greeting %s\n", c->associated_view->name);
                }
                else
                {
                    sprintf(c->answer_buffer, "no greeting\n");
                    c->status = DISCONNECTED;
                }
            }
        }
        else
        {
            sprintf(c->answer_buffer, "NOK\n");
        }
	}
	else if (tokens_len == 1 && !strcmp(parsed_command[0], "status"))
	{
		fish *f;
		// the $ sign in these strings is to be replaced by \n at reception (client side)
		sprintf(c->answer_buffer, "\t->OK : Connecté au contrôleur, %d poisson(s) trouvé(s) $", aquarium__count_fish_in_view(aq, c->associated_view));
		STAILQ_FOREACH(f, &(aq->fish_list), next)
		{
			if (frame__includes_snippet(c->associated_view->frame, f->frame))
			{
			    frame *relative_frame = frame__get_relative(f->frame, c->associated_view->frame);
				sprintf(c->answer_buffer, "%s\tFish %s at %s %s $", c->answer_buffer, f->name, frame__to_str(relative_frame), f->is_started ? "started" : "notStarted");
                free(relative_frame);
			}
		}
        sprintf(c->answer_buffer, "%s\n", c->answer_buffer);
	} else if (tokens_len == 1 && !strcmp(parsed_command[0], "ls"))
    {
        fish *f;
		sprintf(c->answer_buffer, "list ");
		for (int i = 0; i < 3 ; i ++ )
		{
        	STAILQ_FOREACH(f, &(controller->aquarium->fish_list), next)
        	{
            	if (f->is_started && f->position < FISH_PATH_SIZE - 1 && (frame__includes_snippet(c->associated_view->frame, f->path[f->position]) || frame__includes_snippet(c->associated_view->frame, f->path[f->position + 1]))) {
                	frame *relative_frame = frame__get_relative(f->path[f->position], c->associated_view->frame);
                	sprintf(c->answer_buffer, "%s [%s at %s,%d]", c->answer_buffer, f->name, frame__to_str(relative_frame), 5);
                	free(relative_frame);
                	f->position++;
            	} else if (!f->is_started && frame__includes_snippet(c->associated_view->frame, f->frame)) {
                	frame *relative_frame = frame__get_relative(f->frame, c->associated_view->frame);
                	sprintf(c->answer_buffer, "%s [%s at %s,%d]", c->answer_buffer, f->name, frame__to_str(relative_frame), 0);
                	free(relative_frame);
            	}
        	}
        	sprintf(c->answer_buffer, "%s\nlist ", c->answer_buffer);
		}
    }
	else if (tokens_len == 1 && !strcmp(parsed_command[0], "getFishesContinuously"))
	{
		pthread_t t;
		pthread_create(&t, NULL, connection__get_fish_continuously, (void *)c);
	}
	else if (tokens_len == 6 && !strcmp(parsed_command[0], "addFish"))
	{
		frame *f = malloc(sizeof(frame));
		char name[FISH_NAME_MAX_SIZE];
		sscanf(tmp_buffer, "addFish %s at %dx%d, %dx%d, RandomWayPoint", name, &(f->x), &(f->y), &(f->width), &(f->height));
        frame *absolute_frame = frame__get_absolute(f, c->associated_view->frame);
		fish *new_fish = fish__create(name, absolute_frame);
        DEBUG_OUT("adding fish %s with frame %s\n", name, frame__to_str(f));
        free(f);
		if (aquarium__add_fish(aq, new_fish) == -1)
		{
			sprintf(c->answer_buffer, "NOK\n");
		}
		else
		{
			sprintf(c->answer_buffer, "OK\n");
		}
	}
	else if (tokens_len == 2 && !strcmp(parsed_command[0], "delFish"))
	{
        fish *f = aquarium__get_fish(aq, parsed_command[1]);
				if (f == NULL) {
						sprintf(c->answer_buffer, "NOK\n");
				}
        else if ((!f->is_started && frame__includes_snippet(c->associated_view->frame, f->frame)) || (f->is_started && frame__includes_snippet(c->associated_view->frame, f->path[f->position]))) {
            if (aquarium__del_fish(aq, parsed_command[1]) == -1)
            {
                sprintf(c->answer_buffer, "NOK\n");
            }
            else
            {
                sprintf(c->answer_buffer, "OK\n");
            }
        }
        else
        {
            sprintf(c->answer_buffer, "NOK\n");
        }
	}
	else if (tokens_len == 2 && !strcmp(parsed_command[0], "startFish"))
	{
		fish *f = aquarium__get_fish(aq, parsed_command[1]);
		if (f && f->is_started == 0)
		{
            fish__create_path(f, controller->aquarium->frame);
            f->is_started = 1;
			sprintf(c->answer_buffer, "OK\n");
		}
		else
		{
			sprintf(c->answer_buffer, "NOK\n");
		}
	}
	else if (tokens_len == 2 && !strcmp(parsed_command[0], "log") && !strcmp(parsed_command[1], "out"))
	{
		c->status = DISCONNECTED;
		sprintf(c->answer_buffer, "bye\n");
	}
	else
	{
		sprintf(c->answer_buffer, "NOK\n");
	}
}

/**
 * handles a command received from the client's prompt
 * @param c : a pointer to the connection (the client)
 * @param aq : a pointer to the aquarium
 */
void command__from_server(char *command_buffer, char *answer_buffer, aquarium *aq)
{
	char *parsed_command[COMMAND__MAX_SIZE];
	utils__parser(parsed_command, command_buffer, " ");
	int tokens_len = utils__count_tokens(parsed_command);

	if (tokens_len == 2 && !strcmp(parsed_command[0], "load"))
	{
		char path[PATH_MAX_SIZE];
		strcpy(path, "data/");
		strcat(path, parsed_command[1]);
		strcat(path, ".txt");
		FILE *f = fopen(path, "r");
		if(f != NULL)
		{
			aquarium__load(aq, f);
			sprintf(answer_buffer,"\t-> Aquarium loaded ! ( %d display view)", aquarium__count_views(aq));
			fclose(f);
		}
		else
		{
			sprintf(answer_buffer,"\t->NOK");

		}
	}
	else if (tokens_len == 2 && !strcmp(parsed_command[0], "show"))
	{
		view * v;
		sprintf(answer_buffer, "%dx%d", aq->frame->width, aq->frame->height);
		STAILQ_FOREACH(v, &(aq->views_list), next)
		{
			sprintf(answer_buffer, "%s\n%s %dx%d+%d+%d", answer_buffer, v->name, v->frame->x, v->frame->y, v->frame->width, v->frame->height);
		}
	}
	else if (tokens_len == 4 && !strcmp(parsed_command[0], "add") && !strcmp(parsed_command[1], "view"))
	{
		frame *frame = frame__from_str(parsed_command[3]);
		view *v = view__create(parsed_command[2], frame);
		if(aquarium__add_view(aq, v) == -1)
		{
			sprintf(answer_buffer, "\t->NOK");
		}
		else
		{
			sprintf(answer_buffer, "\t-> view added");
		}
	}
	else if (tokens_len == 3 && !strcmp(parsed_command[0], "del") && !strcmp(parsed_command[1], "view"))
	{
		if(aquarium__del_view(aq, parsed_command[2]) == -1)
		{
			sprintf(answer_buffer, "\t->NOK");
		}
		else
		{
			sprintf(answer_buffer,"\t-> view %s deleted", parsed_command[2]);
		}
	}
	else if (tokens_len == 2 && !strcmp(parsed_command[0], "save"))
	{
		aquarium__save(aq, "tst/saved_aq.txt");
		sprintf(answer_buffer,"\t-> Aquarium saved ! ( %d display view)", aquarium__count_views(aq));
	}
	else
	{
		sprintf(answer_buffer,"\t->NOK");
	}
}

/**
 * a function to responde to the command 'getFishesContinuously'. Sould be run on a separate thread
 * @param connection : a pointer to the connection (the client)
 * @return : NULL
 */
void *connection__get_fish_continuously(void *conn)
{
    connection *c = (connection *)conn;
    fish *f;
    while (c->status == CONNECTED && controller->status == CONNECTED)
    {
        sprintf(c->answer_buffer, "list ");
        STAILQ_FOREACH(f, &(controller->aquarium->fish_list), next)
        {
            DEBUG_OUT("f->position = %d\n", f->position);
            DEBUG_OUT("%s in %s ?\n", f->name, c->associated_view->name);
            if (f->is_started &&
                f->position < FISH_PATH_SIZE - 1 &&
                (frame__includes_snippet(c->associated_view->frame, f->path[f->position]) ||
                 frame__includes_snippet(c->associated_view->frame, f->path[f->position + 1]) ||
                 (f->position > 0 &&
                  frame__includes_snippet(c->associated_view->frame, f->path[f->position - 1])
                 ))) {
                frame *relative_frame = frame__get_relative(f->path[f->position], c->associated_view->frame);
                sprintf(c->answer_buffer, "%s [%s at %s,%d]", c->answer_buffer, f->name, frame__to_str(relative_frame), controller->fish_update_interval);
                free(relative_frame);
            } else if (!f->is_started && frame__includes_snippet(c->associated_view->frame, f->frame)) {
                frame *relative_frame = frame__get_relative(f->frame, c->associated_view->frame);
                sprintf(c->answer_buffer, "%s [%s at %s,%d]", c->answer_buffer, f->name, frame__to_str(relative_frame), 0);
                free(relative_frame);
            }
        }
        sprintf(c->answer_buffer, "%s\n", c->answer_buffer);
        write(c->socket_fd, c->answer_buffer, strlen(c->answer_buffer));
        sleep(controller->fish_update_interval);
    }
    pthread_exit(NULL);
}
