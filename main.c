#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[])
{
	MY_STRING a[100]; 
	for (int i = 0; i < 100; i++)
	{
		a[i] = NULL;
	}

	a[0] = my_string_init_c_string("COPY ME!");
	for (int i = 1; i < 100; i++)
	{
		a[i] = my_string_init_copy(a[0]);
	}

	my_string_destroy(a);
	a[0] = my_string_init_c_string("FIRST FIFTY!");
	for (int i = 1; i < 50; i++)
	{
		my_string_assignment(a[i], a[0]);	
	}

	for (int i = 0; i < 50; i++)
	{
		my_string_swap(a[i], a[99 - i]);
	}

	for (int i = 0; i < 100; i++)
	{
		my_string_insertion(a[i], stdout);
		printf(": %d\n", i + 1);
		my_string_destroy(a + i);
	}
 
 return 0;
}
