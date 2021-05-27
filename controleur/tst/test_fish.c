#include "../src/fish.h"
#include "test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int equal_frame(frame *a, frame *b)
{
	if ((a->x == b->x) &&
		(a->y == b->y) &&
		(a->height == b->height) &&
		(a->width == b->width))
		return 1;
	else
		return 0;
}

void fill_frame(frame *a, int x, int y, int width, int height)
{
	a->x = x;
	a->y = y;
	a->width = width;
	a->height = height;
}

int equal_fish(fish *a, fish *b)
{
	if ((!strcmp(a->name, b->name)) &&
		equal_frame(a->frame, b->frame))
		return 1;
	else
		return 0;
}

int main()
{
	fish *fish1, *fish2;
	printf("test of creating fish()\n");
	printf("--------------------------\n");
	fish2 = malloc(sizeof(fish));
	fish2->name = malloc(sizeof(char) *255);
	fish2->frame = malloc(sizeof(frame));
	frame *a = malloc(sizeof(frame));
	strcpy(fish2->name, "test");
	fill_frame(fish2->frame, 100, 150, 20, 25);
	fill_frame(a, 100, 150, 20, 25);
	fish1 = fish__create("test", a);
	print_test(equal_fish(fish1, fish2));
	printf("test of fish__create_path()\n");
	printf("--------------------------\n");
	frame *view = malloc(sizeof(frame));
	fill_frame(view, 0, 0, 500, 500);
	fish__create_path(fish1, view);
	int bool = 1;
	for (int i = 0; i < FISH_PATH_SIZE - 1; i++)
	{
		if (!frame__includes_snippet(fish1->path[i], view)){
            bool = 0;
            break;
		}
	}

	print_test(bool);
	free(fish2->name);
	free(fish2->frame);
	free(view);
	free(fish2);
	fish__free(fish1);
}
