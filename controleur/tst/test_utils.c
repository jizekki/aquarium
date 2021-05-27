#include "../src/utils.h"
#include "test.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int equal_tabs(char **tab1, char **tab2)
{
	int i = 0;
	while (tab1[i] != NULL ||
		tab2[i] != NULL)
	{
		if (strcmp(tab1[i], tab2[i]))
			return 0;
		i++;
	}

	if ((tab2[i] == NULL && tab1[i] != NULL) ||
		(tab2[i] != NULL && tab1[i] == NULL))

		return 0;

	return 1;
}

int main()
{
	char message1[] = "dish not fish ";
	char *parsed_message1[10];
	char *expected_parse[10] = { "dish", "not", "fish", NULL
	};
	char *empty_parse[10] = {};

	printf("test of utils__parser()\n");
	printf("--------------------------\n");
	utils__parser(parsed_message1, message1, " ");
	print_test(equal_tabs(expected_parse, parsed_message1));

	printf("test of utils__count_tokens()\n");
	printf("--------------------------\n");
	print_test(utils__count_tokens(expected_parse) == 3 &&
		utils__count_tokens(empty_parse) == 0);

}