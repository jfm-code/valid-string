#include <stdio.h>
#include <stdlib.h>
#include "status.h"
#include "stack.h"
#include "logger.h"

int main()
{
	int num_of_string = 0;
	int noc;
	LOG_DEBUG("Please enter the number of strings: ");
	noc = scanf("%d", &num_of_string);
	if (noc != 1)
	{
		LOG_DEBUG("Please enter again the number of strings: ");
		noc = scanf("%d", &num_of_string);
	}
	for (int i = 0; i < num_of_string; i++)
	{
		char* str[10];
		LOG_DEBUG("Please enter a string: ");
		scanf("%s", &str);
		clear_keyboard_buffer();
		LOG_DEBUG("The string is %s\n", str);
		if (check_string(str) == TRUE)
		{
			LOG_CRITICAL("Yes\n");
		}
		else 
		{
			LOG_CRITICAL("No\n");
		}
	}
	return 0;
}
