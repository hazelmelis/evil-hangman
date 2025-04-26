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

void print_tree(Node* root);
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);
void tree_insert(Node** root, MY_STRING word, MY_STRING key);
void find_largest_word_family(Node* root, Node** largest);
void destroy_tree(Node** root);

#endif
