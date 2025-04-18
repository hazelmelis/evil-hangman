#ifndef ASSOC_ARRAY_H
#define ASSOC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include "generic.h"
#include "generic_vector.h"
#include "my_string.h"

typedef struct node Node;
struct node
{
	GENERIC_VECTOR my_strings;
	MY_STRING key;
	Node* left;
	Node* right;
};

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);
//void assoc_array_insert(ASSOC_ARRAY assoc_array, MY_STRING new_string, MY_STRING current_key);

#endif
