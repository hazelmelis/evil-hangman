#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "my_string.h"
#include "generic_vector.h"
#include "node.h"

void clear_keyboard_buffer();
void get_word_length(int* pLength);
void get_number_of_guesses(int* pGuesses);
void ask_about_word_list(Boolean* print_word_list);
void get_guess(char* pGuess, Node* temp, Boolean print_word_list);
GENERIC_VECTOR get_new_word_list(char guess, GENERIC_VECTOR current_word_list, MY_STRING current_key);
void print(Node* root);

int main(int argc, char* argv[])
{
	GENERIC_VECTOR dictionary_strings[30];
	for (int i = 0; i < 30; i++)
	{
		dictionary_strings[i] = generic_vector_init_default(my_string_init_copy, my_string_destroy);
	}
	FILE* fp = fopen("dictionary.txt", "r");	
	MY_STRING extract = my_string_init_default();
	while (my_string_extraction(extract, fp) == SUCCESS)
	{
		int index = my_string_get_size(extract);
		generic_vector_push_back(dictionary_strings[index], extract);
	}
	my_string_destroy(&extract);
	fclose(fp);

	printf("**********");	
	printf("****************************************** LET'S PLAY HANGMAN! *******************************************");
	printf("**********\n");	

	int word_length;
	get_word_length(&word_length);	

	Node* temp = malloc(sizeof(Node));
	temp->my_strings = generic_vector_init_default(my_string_init_copy, my_string_destroy);
	temp->left = NULL;
	temp->right = NULL;

	for (int i = 0; i < generic_vector_get_size(dictionary_strings[word_length]); ++i)
	{
		generic_vector_push_back(temp->my_strings, generic_vector_at(dictionary_strings[word_length], i));
	}
	
	for (int i = 0; i < 30; ++i)
	{
		generic_vector_destroy(dictionary_strings + i);	
	}


	MY_STRING init_key = my_string_init_default();
	for (int i = 0; i < word_length; ++i)
	{
		my_string_push_back(init_key, '-');
	}	
	temp->key = init_key;
	MY_STRING new_key = my_string_init_default();

	Boolean print_word_list;
	ask_about_word_list(&print_word_list);

	int total_guesses;
	get_number_of_guesses(&total_guesses);
	MY_STRING prev_guesses = my_string_init_default();

	if (print_word_list == TRUE)
	{
		printf("Word list partition\n");
		print(temp);
		printf("\n");
	}

	printf("Guesses remaining: %d\n", total_guesses);
	printf("Used letters:");
	for (int i = 0; i < my_string_get_size(prev_guesses); ++i)
	{
		printf(" %c", *my_string_at(prev_guesses, i));
	}
	printf("\nWord: %s\n", my_string_c_str(temp->key));
		
	char guess;
	get_guess(&guess, temp, print_word_list);
//partition 
	
//*************************************************************************************
//****************************************************************************************

	Node* root = NULL;
	for (int i = 0; i < generic_vector_get_size(temp->my_strings); ++i)
	{	
		get_word_key_value(temp->key, new_key, generic_vector_at(temp->my_strings, i), guess);	
		check_tree(&root, generic_vector_at(temp->my_strings, i), new_key); 
	}
	print(root);

	Node* largest = root;
	find_largest_word_family(root, largest);

	int size = generic_vector_get_size(temp->my_strings);
	for (int i = 0; i < size; ++i)
	{
		generic_vector_pop_back(temp->my_strings);
	}
	for (int i = 0; i < generic_vector_get_size(largest->my_strings); ++i)
	{
		generic_vector_push_back(temp->my_strings, generic_vector_at(largest->my_strings, i));
	}

	my_string_swap(temp->key, largest->key);	

	destroy_tree(&root);

	printf("\nsize of largest: %d\n", generic_vector_get_size(temp->my_strings));
	printf("key: %s\n", my_string_c_str(temp->key));
	
	int rand_index;
	srand(time(NULL));
	rand_index = rand() % generic_vector_get_size(temp->my_strings);

	
	
	my_string_destroy(&new_key);
	my_string_destroy(&prev_guesses);
	destroy_tree(&temp);
	
 	return 0;
}

void print(Node* root)
{
	if (root == NULL) return;
	print(root->left);
	printf("%s %d\n", my_string_c_str(root->key), generic_vector_get_size(root->my_strings));
	print(root->right);
}
/*
GENERIC_VECTOR get_new_word_list(char guess, GENERIC_VECTOR current_word_list, MY_STRING current_key)
{
	Node* root = NULL;
	MY_STRING new_key = my_string_init_default();
	for (int i = 0; i < generic_vector_get_size(current_word_list); ++i)
	{	
		get_word_key_value(current_key, new_key, generic_vector_at(current_word_list, i), guess);
	
		check_tree(root, generic_vector_at(current_word_list, i), new_key); 
	}

	Node* largest = root;
	find_largest_word_family(root, &largest);
	
	my_string_assignment(current_key, largest->key);
	GENERIC_VECTOR temp = largest->my_strings;

//	largest->my_strings = NULL;
	
	//destroy
	return temp;	
}
*/

void clear_keyboard_buffer(void)
{
	char c;
	do
	{
		scanf("%c", &c);
	} 
	while (c != '\n');
}

void get_word_length(int* pLength)
{
		
	printf("Enter your desired word length: ");
	int noc = scanf(" %d", pLength);
	while (noc != 1 || *pLength <= 1 || *pLength == 23 || (*pLength >= 25 && *pLength <= 27) || *pLength > 29)
	{
		printf("There are no words of that length. Try again: ");
		clear_keyboard_buffer();
		noc = scanf(" %d", pLength);
	}
	printf("Great! I'm thinking of a word with %d letters.\n", *pLength);
}


void get_number_of_guesses(int* pGuesses)
{
	printf("Enter the number of guesses you want: ");
	int noc = scanf(" %d", pGuesses);
	while (noc != 1 || *pGuesses < 1)
	{
		printf("You'll need at least one guess! Try again: ");
		clear_keyboard_buffer();
		noc = scanf(" %d", pGuesses);
	}
	if (*pGuesses == 1) printf("That's bold! You only have 1 chance to guess my word.\n\n");
	else printf("Alright, you have %d chances to guess my word.\n\n", *pGuesses);
}

void ask_about_word_list(Boolean* print_word_list)
{
	
	printf("(For grading purposes) would you like a running total of the words remaining in the word list? (y/n): ");
	char input;
	scanf(" %c", &input);
	while (input != 'Y' && input != 'y' && input != 'N' && input != 'n')
	{
		printf("Invalid answer. Enter 'y' or 'n': ");
		clear_keyboard_buffer();
		scanf(" %c", &input);
	}
	clear_keyboard_buffer();

	*print_word_list = (input == 'y' || input == 'Y') ? TRUE : FALSE;
}

void get_guess(char* pGuess, Node* temp, Boolean print_word_list)
{
	printf("Guess a letter: ");
	scanf(" %c", pGuess);
	
	while (!isalpha(*pGuess))
	{
		printf("That's not a letter. Try again: ");
		clear_keyboard_buffer();
		scanf(" %c", pGuess);
	}
	clear_keyboard_buffer();

	*pGuess = tolower(*pGuess);
}


