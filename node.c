#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"
#include <ctype.h>

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

