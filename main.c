#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"
#include "node.h"

void clear_keyboard_buffer();
void get_word_length(int* pLength);
void get_number_of_guesses(int* pGuesses);
void ask_about_word_list(Boolean* print_word_list);
void get_guess(char* pGuess, GENERIC_VECTOR word_list, Boolean print_word_list);

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
	int noc;

	int word_length;
	get_word_length(&word_length);	
	GENERIC_VECTOR current_word_list = dictionary_strings[word_length];
	MY_STRING current_key = my_string_init_default();
	for (int i = 0; i < word_length; ++i)
	{
		my_string_push_back(current_key, '-');
	}
	my_string_destroy(&current_key);

	Boolean print_word_list;
	ask_about_word_list(&print_word_list);

	int guesses;
	get_number_of_guesses(&guesses);
	
	char guess;
	get_guess(&guess, current_word_list, print_word_list);	

	for (int i = 0; i < 30; i++)
	{
		generic_vector_destroy(dictionary_strings + i);
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

void get_guess(char* pGuess, GENERIC_VECTOR word_list, Boolean print_word_list)
{
	if (print_word_list == TRUE)
	{
		printf("Words remaining in word list: %d\n", generic_vector_get_size(word_list));
	}
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
