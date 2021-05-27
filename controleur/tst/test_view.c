#include "../src/view.h"
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

int equal_view(view *a, view *b)
{
	if ((!strcmp(a->name, b->name)) &&
		equal_frame(a->frame, b->frame))
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

int main()
{
	view *view1, *view2;
	view2 = malloc(sizeof(view));
	view2->name = malloc(sizeof(char) *255);
	view2->frame = malloc(sizeof(frame));
	frame *a = malloc(sizeof(frame));
	printf("test of creating view\n");
	printf("--------------------------\n");
	strcpy(view2->name, "test");
	fill_frame(view2->frame, 100, 150, 20, 25);
	fill_frame(a, 100, 150, 20, 25);
	view1 = view__create("test", a);
	print_test(equal_view(view1, view2));
	view__free(view1);
	view__free(view2);
	return 0;
}