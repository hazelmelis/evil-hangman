#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "assoc_array.h"

typedef struct assoc_array Assoc_array;
struct assoc_array
{
	MY_STRING hKey;
	GENERIC_VECTOR hStrings;
};

typedef struct node Node;
struct Node
{
	Assoc_array data;
	int level;
	Node* left;
	Node* right;
};

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	for (int i = 0; i < my_string_get_size(word); i++)
	{
		if (*my_string_at(word, i) == tolower(guess) || *my_string_at(word, i) == toupper(guess))
		{
			*my_string_at(current_word_family, i) = tolower(guess);
		}
	}

	return my_string_assignment(new_key, current_word_family);
}
