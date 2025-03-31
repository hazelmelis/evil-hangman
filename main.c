#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"

int main(int argc, char* argv[])
{

	MY_STRING hS = my_string_init_c_string("");
	MY_STRING hSh = my_string_init_c_string("a");

	printf("%d\n", my_string_compare(hS, hSh));
	my_string_pop_back(hSh);

	printf("%d\n", my_string_compare(hS, hSh));
	my_string_destroy(&hS);
	my_string_destroy(&hSh);
/*
	GENERIC_VECTOR a[30];
	for (int i = 0; i < 30; i++)
	{
		a[i] = generic_vector_init_default(my_string_init_copy, my_string_destroy);
	}
	
	FILE* fp = fopen("dictionary.txt", "r");	
	MY_STRING hExtract = my_string_init_default();
	while (my_string_extraction(hExtract, fp) == SUCCESS)
	{
		int index = my_string_get_size(hExtract);
		generic_vector_push_back(a[index], my_string_init_copy(hExtract));
	}

	for (int i = 0; i < 30; ++i)
	{
		printf("WORDS OF SIZE %d: %d\n", i, generic_vector_get_size(a[i]));
	}


	fclose(fp);
*/
	
 return 0;
}
