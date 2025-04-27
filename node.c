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

void tree_insert(Node** root, MY_STRING word, MY_STRING key, int depth)
{
	if ((*root) == NULL)
	{
		Node* new_node = malloc(sizeof(Node));
	
		new_node->depth = depth;	
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
			depth++;
			tree_insert(&((*root)->left), word, key, depth);
		}
		else if (my_string_compare(key, (*root)->key) > 0)
		{
			depth++;
			tree_insert(&((*root)->right), word, key, depth);
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

void find_max_depth(Node* root, int* max)
{
	if (root == NULL) return;

	find_max_depth(root->left, max);
	if (root->depth > *max)
	{
		*max = root->depth;
	}
	find_max_depth(root->right, max);
}

int get_balance_factor(Node* root)
{
	int right_depth = 0;
	int left_depth = 0;

	if (root == NULL) return 777;

	if (root->left == NULL && root->right == NULL) return 0;

	if (root->left == NULL)
	{
		left_depth = root->depth;
	}
	else
	{
		find_max_depth(root->left, &left_depth);
	}

	if (root->right == NULL)
	{
		right_depth = root->depth;
	}
	else
	{
		find_max_depth(root->right, &right_depth);
	}

	return right_depth - left_depth;
}

void check_for_balance(Node** root)
{
	if (*root == NULL) return; 

	check_for_balance(&((*root)->left));
	check_for_balance(&((*root)->right));

	if (get_balance_factor(*root) >= 2)
	{
		if (get_balance_factor((*root)->right) < 0)
		{
			double_left_rotation(root);
		}
		else
		{
			left_rotation(root);
		}
	}
		
	else if (get_balance_factor(*root) <= -2)
	{
		if (get_balance_factor((*root)->left) > 0)
		{
			double_right_rotation(root);
		}
		else
		{
			right_rotation(root);
		}
	}
}

void right_rotation(Node** root)
{
	if (root == NULL || *root == NULL ) return;

	Node* new_root = (*root)->left;

	Node* new_right = *root;
	adjust_depths(&((*root)->right), 1);

	new_right->left = new_root->right;

	new_root->right = new_right;

	*root = new_root;
}

void left_rotation(Node** pRoot)
{
	if (pRoot == NULL || *pRoot == NULL ) return;

	Node* new_root = (*pRoot)->right;

	Node* new_left = *pRoot;

	new_left->right = new_root->left;

	new_root->left = new_left;

	*pRoot = new_root;
}

void double_right_rotation(Node** pRoot)
{
	left_rotation(&((*pRoot)->left));
	right_rotation(pRoot);
}

void double_left_rotation(Node** pRoot)
{
	right_rotation(&((*pRoot)->right));
	left_rotation(pRoot);
}

void adjust_depths(Node** root, int depth)
{
	if (root == NULL || *root == NULL) return; 

	adjust_depths(&((*root)->left), depth + 1);
	(*root)->depth = depth;
	adjust_depths(&((*root)->right), depth + 1);
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
	
	
