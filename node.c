#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "my_string.h"
#include "generic_vector.h"
#include "node.h"

void print_tree(Node* root)
{
	if (root == NULL) return;
	print_tree(root->left);
	printf("%s %d\n", my_string_c_str(root->key), generic_vector_get_size(root->my_strings));
	print_tree(root->right);
}

Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	guess = tolower(guess);
	for (int i = 0; i < my_string_get_size(word); i++)
	{
		if (*my_string_at(word, i) == guess)
		{
			*my_string_at(new_key, i) = guess;
		}
	}

	return SUCCESS;
}

void tree_insert(Node** root, MY_STRING word, MY_STRING key)
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
			tree_insert(&((*root)->left), word, key);
		}
		else if (my_string_compare(key, (*root)->key) > 0)
		{
			tree_insert(&((*root)->right), word, key);
		}
		else if (my_string_compare(key, (*root)->key) == 0)
		{
			generic_vector_push_back((*root)->my_strings, word);
		}	
	}
}


void find_largest_word_family(Node* root, Node** largest)
{
	int heads;
	if (root == NULL) return;
	
	find_largest_word_family(root->left, largest);
	if (generic_vector_get_size(root->my_strings) > generic_vector_get_size((*largest)->my_strings))
	{
		*largest = root;
	}
	else if (generic_vector_get_size(root->my_strings) == generic_vector_get_size((*largest)->my_strings))
	{
		heads = rand() % 2;
		if (heads)
		{
			*largest = root;
		}
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
	
	
