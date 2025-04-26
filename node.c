#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"
#include "node.h"
#include <ctype.h>

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	for (int i = 0; i < my_string_get_size(word); i++)
	{
		if (*my_string_at(word, i) == tolower(guess) || *my_string_at(word, i) == toupper(guess))
		{
			*my_string_at(current_word_family, i) = tolower(guess);
		}
		else
		{
			*my_string_at(current_word_family, i) = '-';
		}
	}

	return my_string_assignment(new_key, current_word_family);
}

void check_tree(Node** root, MY_STRING word, MY_STRING key)
{
	if ((*root) == NULL)
	{
		Node* new_node = malloc(sizeof(Node));
		
		new_node->my_strings = generic_vector_init_default(my_string_init_copy, my_string_destroy);
		generic_vector_push_back(new_node->my_strings, word);

		new_node->key = my_string_init_copy(key);

		new_node->left = NULL;
		new_node->right = NULL;

		*root = new_node;
	}
	else
	{
		if (my_string_compare(key, (*root)->key) < 0)
		{
			check_tree(&((*root)->left), word, key);
		}
		else if (my_string_compare(key, (*root)->key) > 0)
		{
			check_tree(&((*root)->right), word, key);
		}
		else if (my_string_compare(key, (*root)->key) == 0)
		{
			generic_vector_push_back((*root)->my_strings, word);
		}	
	}
}


void find_largest_word_family(Node* root, Node* largest)
{	
	if (root == NULL) return;
	
	find_largest_word_family(root->left, largest);
	if (generic_vector_get_size(root->my_strings) > generic_vector_get_size(largest->my_strings))
	{
		largest = root;
	}
	find_largest_word_family(root->right, largest);	
}

void destroy_tree(Node** root)
{
	if (*root == NULL) return;

	destroy_tree(&((*root)->left));

	destroy_tree(&((*root)->right));
	
	generic_vector_destroy(&((*root)->my_strings));
	my_string_destroy(&((*root)->key));
	free(*root);
	*root = NULL;
}
	
	
