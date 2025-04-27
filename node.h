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
	int depth;
	Node* left;
	Node* right;
};

void print_tree(Node* root);
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess);
void tree_insert(Node** root, MY_STRING word, MY_STRING key, int depth);
void find_largest_word_family(Node* root, Node** largest);
void find_max_depth(Node* root, int* max);
int get_balance_factor(Node* root);
void check_for_balance(Node** root);
void right_rotation(Node** root);
void left_rotation(Node** pRoot);
void double_right_rotation(Node** pRoot);
void double_left_rotation(Node** pRoot);
void adjust_depths(Node** root, int depth);
void destroy_tree(Node** root);

#endif
