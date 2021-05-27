#include "../src/aquarium.h"
#include "../src/view.h"
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

int main()
{
  aquarium * aquarium;
  frame *frame1, *frame2, *frame3;
  frame1 = malloc(sizeof(*frame1));
  printf("test of aquarium__empty()\n");
  printf("--------------------------\n");
  fill_frame(frame1, 0, 0, 1000, 1000);
  aquarium = aquarium__empty();
  print_test(equal_frame(frame1, aquarium->frame));
  aquarium__free(aquarium);

  printf("test of aquarium__load()\n");
  printf("--------------------------\n");
  aquarium = malloc(sizeof(*aquarium));
  frame3 = malloc(sizeof(*frame3));
  fill_frame(frame3, 500, 0, 500, 1000);
  FILE *f = fopen("tst/test_aquarium.txt", "r");
  aquarium__load(aquarium, f);
  view *v1, *v2;
  v1 = STAILQ_FIRST(&(aquarium->views_list));
  v2 = STAILQ_NEXT(v1, next);
  print_test(aquarium->frame->height == 1000 &&
    aquarium->frame->width == 1000 &&
    equal_frame(frame3, v1->frame) &&
    !strcmp("Test", v1->name) &&
    v2 == NULL);

  fclose(f);
  free(frame3);
  aquarium__free(aquarium);

  printf("test of aquarium__add_fish()\n");
  printf("--------------------------\n");
  fill_frame(frame1, 20, 30, 10, 12);
  fish *test_fish = fish__create("test", frame1);
  aquarium = aquarium__empty();
  int bool1 = aquarium__add_fish(aquarium, test_fish);
  int bool2 = aquarium__add_fish(aquarium, test_fish);
  fish *firstfish = STAILQ_FIRST(&(aquarium->fish_list));
  print_test((!bool1 && bool2) &&
    test_fish == firstfish &&
    NULL == STAILQ_NEXT(firstfish, next));
  aquarium__free(aquarium);

  printf("test of aquarium__get_fish()\n");
  printf("--------------------------\n");
  aquarium = aquarium__empty();
  frame1 = malloc(sizeof(*frame1));
  fill_frame(frame1, 20, 30, 10, 12);
  test_fish = fish__create("test", frame1);
  aquarium__add_fish(aquarium, test_fish);
  bool1 = (aquarium__get_fish(aquarium, "test") == test_fish);
  bool2 = (aquarium__get_fish(aquarium, "not in fish list") == NULL);
  print_test(aquarium__get_fish(aquarium, "test") == test_fish &&
    aquarium__get_fish(aquarium, "not in fish list") == NULL);
  aquarium__free(aquarium);

  printf("test of aquarium__del_fish()\n");
  printf("--------------------------\n");
  aquarium = aquarium__empty();
  frame1 = malloc(sizeof(*frame1));
  fill_frame(frame1, 20, 30, 10, 12);
  frame2 = malloc(sizeof(*frame2));
  fill_frame(frame2, 20, 30, 10, 12);
  test_fish = fish__create("test", frame1);
  aquarium__add_fish(aquarium, test_fish);
  fish *another_test_fish = fish__create("another_test", frame2);
  aquarium__add_fish(aquarium, another_test_fish);
  aquarium__del_fish(aquarium, "test");
  print_test(aquarium__get_fish(aquarium, "another_test") &&
    aquarium__get_fish(aquarium, "test") == NULL &&
    aquarium__del_fish(aquarium, "not in list") == -1);
  aquarium__free(aquarium);

  printf("test of aquarium__add_view()\n");
  printf("--------------------------\n");
  frame1 = malloc(sizeof(*frame1));
  fill_frame(frame1, 0, 0, 500, 500);
  view *test_view = view__create("test", frame1);
  aquarium = aquarium__empty();
  bool1 = aquarium__add_view(aquarium, test_view);
  bool2 = aquarium__add_view(aquarium, test_view);
  view *first_view = STAILQ_FIRST(&(aquarium->views_list));
  print_test((!bool1 && bool2) &&
    test_view == first_view &&
    NULL == STAILQ_NEXT(first_view, next));
  aquarium__free(aquarium);

  printf("test of aquarium__get_view()\n");
  printf("--------------------------\n");
  aquarium = aquarium__empty();
  frame1 = malloc(sizeof(*frame1));
  fill_frame(frame1, 0, 0, 500, 500);
  test_view = view__create("test", frame1);
  aquarium__add_view(aquarium, test_view);
  bool1 = (aquarium__get_view(aquarium, "test") == test_view);
  bool2 = (aquarium__get_view(aquarium, "not in view list") == NULL);
  print_test(aquarium__get_view(aquarium, "test") == test_view &&
    aquarium__get_view(aquarium, "not in view list") == NULL);
  aquarium__free(aquarium);

  printf("test of aquarium__del_view()\n");
  printf("--------------------------\n");
  aquarium = aquarium__empty();
  frame1 = malloc(sizeof(*frame1));
  frame2 = malloc(sizeof(*frame2));
  fill_frame(frame1, 0, 0, 500, 500);
  fill_frame(frame2, 0, 0, 500, 500);
  test_view = view__create("test", frame1);
  aquarium__add_view(aquarium, test_view);
  view *another_test_view = view__create("another_test", frame2);
  aquarium__add_view(aquarium, another_test_view);
  aquarium__del_view(aquarium, "test");
  print_test(aquarium__get_view(aquarium, "another_test") &&
    aquarium__get_view(aquarium, "test") == NULL &&
    aquarium__del_view(aquarium, "not in list") == -1);
  aquarium__free(aquarium);

  printf("test of aquarium__count_views()\n");
  printf("--------------------------\n");
  aquarium = aquarium__empty();
  bool1 = (aquarium__count_views(aquarium) == 0);
  frame1 = malloc(sizeof(*frame1));
  fill_frame(frame1, 0, 0, 500, 500);
  test_view = view__create("test", frame1);
  aquarium__add_view(aquarium, test_view);
  bool2 = (aquarium__count_views(aquarium) == 1);
  print_test(bool1 && bool2);
  aquarium__free(aquarium);

  printf("test of aquarium__count_fish_in_view()\n");
  printf("--------------------------\n");
  aquarium = aquarium__empty();
  frame1 = malloc(sizeof(*frame1));
  fill_frame(frame1, 0, 0, 500, 500);
  test_view = view__create("test", frame1);
  aquarium__add_view(aquarium, test_view);
  bool1 = aquarium__count_fish_in_view(aquarium, test_view);
  frame2 = malloc(sizeof(*frame2));
  fill_frame(frame2, 20, 30, 10, 12);
  test_fish = fish__create("test_fish", frame2);
  aquarium__add_fish(aquarium, test_fish);
  bool2 = (aquarium__count_fish_in_view(aquarium, test_view) == 1);
  aquarium__del_fish(aquarium, "test_fish");
  print_test(!bool1 && bool2 && !aquarium__count_fish_in_view(aquarium, test_view));
  aquarium__free(aquarium);
}