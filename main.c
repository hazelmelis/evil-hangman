#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>
#include "my_string.h"
#include "generic_vector.h"
#include "node.h"

#define LETTERS_IN_ALPHABET 26

void clear_keyboard_buffer();
int get_word_length();
int get_number_of_guesses();
Boolean ask_about_word_list();
char get_guess(int* alphabet);
GENERIC_VECTOR get_new_word_list(char guess, GENERIC_VECTOR current_word_list, MY_STRING current_key);
int user_wishes_to_continue();

int main(int argc, char* argv[])
{
	int wishes_to_continue = 1;
	while (wishes_to_continue)
	{
		// Partition entire dictionary into vectors according to word length 
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


		// Begin game interface
		printf("**********");	
		printf("****************************************** LET'S PLAY HANGMAN! *******************************************");
		printf("**********\n");	

		// Ask user for word length
		int word_length = get_word_length();

		// Initialize temp node. To be used and updated after each guess
		Node* temp = malloc(sizeof(Node));
		temp->my_strings = generic_vector_init_default(my_string_init_copy, my_string_destroy);
		temp->depth = 0;
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

		// Ask grader if they want to see the word list partitions
		Boolean print_word_list = ask_about_word_list();  

		// Ask user how many guesses
		int total_guesses = get_number_of_guesses();
		int alphabet[26] = { 0 };

		if (print_word_list == TRUE)
		{
			printf("\nWord list partition\n");
			print_tree(temp);
			printf("\n");
		}

		int contains_blanks = 1;


		while (total_guesses > 0 && contains_blanks)
		{
			temp->depth = 0;
			//printf("largest key: %s   size: %d\n", my_string_c_str(temp->key), generic_vector_get_size(temp->my_strings));

			printf("Guesses remaining: %d\n", total_guesses);
			printf("Used letters:");
			for (int i = 0; i < LETTERS_IN_ALPHABET; ++i)
			{
				if (alphabet[i])
				{
					int letter = i + 'a';
					printf(" %c", letter);
				}
			}
			printf("\nWord: %s\n", my_string_c_str(temp->key));
			
			char guess = get_guess(alphabet);

			Node* root = NULL;
			for (int i = 0; i < generic_vector_get_size(temp->my_strings); ++i)
			{
				MY_STRING extract_key = my_string_init_copy(temp->key);	
				
				get_word_key_value(temp->key, extract_key, generic_vector_at(temp->my_strings, i), guess);
			
				tree_insert(&root, generic_vector_at(temp->my_strings, i), extract_key, temp->depth); 
				check_for_balance(&root);
				adjust_depths(&root, 0);

				my_string_destroy(&extract_key);
			}
	
			Node* largest_node = root;
			srand(time(NULL));
			find_largest_word_family(root, &largest_node);
			
			int size = generic_vector_get_size(temp->my_strings);
			for (int i = 0; i < size; ++i)
			{
				generic_vector_pop_back(temp->my_strings);
			}
			for (int i = 0; i < generic_vector_get_size(largest_node->my_strings); ++i)
			{
				generic_vector_push_back(temp->my_strings, generic_vector_at(largest_node->my_strings, i));
			}
			
			my_string_assignment(temp->key, largest_node->key);

			for (int i = 0; i < word_length; ++i)
			{
				if (*my_string_at(temp->key, i) == guess) 
				{
					total_guesses++;
					break;
				}
			}	
			total_guesses--;
			
			contains_blanks = 0;
			for (int i = 0; i < word_length; ++i)
			{
				if (*my_string_at(temp->key, i) == '-')
				{
					contains_blanks = 1;
				}
			}

			if (print_word_list == TRUE)
			{
				printf("\n\nWord list partition\n");
				print_tree(root);
				printf("\n");
			}
			else printf("\n");
			destroy_tree(&root);

		}

		if (!contains_blanks)
		{
			printf("Wow, you won! Congratulations!\n");
			printf("I was indeed thinking of \"%s\" this whole time!\n\n", my_string_c_str(temp->key));
		}
		else
		{
			int rand_index;
			rand_index = rand() % generic_vector_get_size(temp->my_strings);
			MY_STRING winning_word = generic_vector_at(temp->my_strings, rand_index);

			printf("HA HA, YOU LOST\n");
			printf("I was thinking of \"%s\"\n\n", my_string_c_str(winning_word));
		}	
		
		destroy_tree(&temp);
		
		wishes_to_continue = user_wishes_to_continue();
	}
	
 	return 0;
}

void clear_keyboard_buffer(void)
{
	char c;
	do
	{
		scanf("%c", &c);
	} 
	while (c != '\n');
}

int get_word_length()
{
	int input;		
	printf("Enter your desired word length: ");
	int noc = scanf(" %d", &input);
	while (noc != 1 || input <= 1 || input == 23 || (input >= 25 && input <= 27) || input > 29)
	{
		printf("There are no words of that length. Try again: ");
		clear_keyboard_buffer();
		noc = scanf(" %d", &input);
	}
	printf("Great! I'm thinking of a word with %d letters.\n", input);
	
	return input;
}


int get_number_of_guesses()
{
	int input;
	printf("Enter the number of guesses you want: ");
	int noc = scanf(" %d", &input);
	while (noc != 1 || input < 1)
	{
		printf("You'll need at least one guess! Try again: ");
		clear_keyboard_buffer();
		noc = scanf(" %d", &input);
	}
	if (input == 1) printf("That's bold! You only have 1 chance to guess my word.\n\n");
	else printf("Alright, you have %d chances to guess my word.\n\n", input);

	return input;
}

Boolean ask_about_word_list()
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

	return (input == 'y' || input == 'Y') ? TRUE : FALSE;
}

char get_guess(int* alphabet)
{
	char input;
	printf("Guess a letter: ");
	scanf(" %c", &input);

	int already_guessed = 1;

	while (!isalpha(input) || already_guessed)
	{
		if (!isalpha(input))
		{	
			printf("That's not a letter. Try again: ");
			clear_keyboard_buffer();
			scanf(" %c", &input);
		}
		else
		{
			already_guessed = alphabet[input - 'a'];

			if (already_guessed)
			{
				printf("You've already guessed that letter! Try again: ");
				clear_keyboard_buffer();
				scanf(" %c", &input);	
			}
		}
	}
	clear_keyboard_buffer();

	alphabet[input - 'a'] = 1;

	return input;
}

int user_wishes_to_continue()
{
	char input; 
	printf("Want to play again? (y/n): ");
	scanf(" %c", &input);

	while (input != 'y' && input != 'Y' && input != 'n' && input != 'N')
	{
		printf("Invalid answer. Enter 'y' or 'n': ");
		clear_keyboard_buffer();
		scanf(" %c", &input);	
	}
	clear_keyboard_buffer();

	printf("\n");
	
	return input == 'y' || input == 'Y';
}

