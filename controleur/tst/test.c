#include <stdio.h>
#include <stdlib.h>

void test_success()
{
  printf("\t\033[32m PASSED \033[00m\n");
}

void test_fail()
{
  printf("\t\033[31m FAILED \033[00m\n");
}

void print_test(int test)
{
  if (test)
    test_success();
  else
    test_fail();
}