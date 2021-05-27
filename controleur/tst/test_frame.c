#include "../src/frame.h"
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

int main()
{
	frame *frame1, *frame2, *frame3, *viewer1, *viewer2, *viewer3;
	frame2 = malloc(sizeof(frame));
	viewer1 = malloc(sizeof(frame));
	viewer2 = malloc(sizeof(frame));
	viewer3 = malloc(sizeof(frame));

	fill_frame(frame2, 245, 245, 20, 20);
	fill_frame(viewer1, 0, 0, 500, 500);
	fill_frame(viewer2, 500, 500, 500, 500);
	fill_frame(viewer3, 250, 250, 500, 500);

	printf("test of frame__from_str()\n");
	printf("--------------------------\n");
	frame1 = frame__from_str("245x245+20+20");
	print_test(equal_frame(frame1, frame2));

	printf("test of frame__to_str()\n");
	printf("--------------------------\n");
	char *str = frame__to_str(frame2);
	print_test(!strcmp(str, "245x245,20x20"));
	free(str);

	printf("test of frame__includes_snippet()\n");
	printf("--------------------------\n");
	print_test(frame__includes_snippet(frame1, viewer1) &&
		!frame__includes_snippet(frame1, viewer2) &&
		frame__includes_snippet(frame2, viewer3));

	printf("test of frame__move_randomly_inside()\n");
	printf("--------------------------\n");
	fill_frame(frame2, 200, 250, 10, 15);
	frame__move_randomly_inside(frame2, viewer1);
	print_test((!equal_frame(frame2, frame1)) &&
		frame__includes_snippet(frame2, viewer1));

	printf("test of frame__get_absolute()\n");
	printf("--------------------------\n");
	fill_frame(frame1, 200, 250, 10, 15);
	fill_frame(frame2, 1000, 1250, 50, 75);
	frame3 = frame__get_absolute(frame1, viewer1);
	print_test(equal_frame(frame2, frame3));

	printf("test of frame__get_relative()\n");
	printf("--------------------------\n");
	free(frame2);
	frame2 = frame__get_relative(frame3, viewer1);
	print_test(equal_frame(frame1, frame2));

	free(frame3);
	free(frame2);
	free(frame1);
	free(viewer1);
	free(viewer2);
	free(viewer3);
	return 0;
}