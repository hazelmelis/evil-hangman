#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"
#include "generic_vector.h"
#include "assoc_array.h"

void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{
	MY_STRING word = my_string_init_c_string("The");
	MY_STRING current = my_string_init_c_string("---");
	MY_STRING new = my_string_init_default();
	get_word_key_value(current, new, word, 't');
	printf("%s\n", my_string_c_str(new));
	
	
	MY_STRING word2 = my_string_init_c_string("Truck");
	MY_STRING current2 = my_string_init_c_string("-----");
	MY_STRING new2 = my_string_init_default();
	get_word_key_value(current2, new2, word2, 'r');
	printf("%s\n", my_string_c_str(new2));
	MY_STRING word3 = my_string_init_c_string("happy");
	MY_STRING current3 = my_string_init_c_string("--ppy");
	MY_STRING new3 = my_string_init_default();
	get_word_key_value(current3, new3, word3, 'h');
	printf("%s\n", my_string_c_str(new3));
	MY_STRING word4 = my_string_init_c_string("awesome");
	MY_STRING current4 = my_string_init_c_string("--e---e");
	MY_STRING new4 = my_string_init_default();
	get_word_key_value(current4, new4, word4, 'z');
	printf("%s\n", my_string_c_str(new4));

	my_string_destroy(&current);
	my_string_destroy(&current2);
	my_string_destroy(&current3);
	my_string_destroy(&current4);
	my_string_destroy(&word);
	my_string_destroy(&word2);
	my_string_destroy(&word3);
	my_string_destroy(&word4);
	my_string_destroy(&new);
	my_string_destroy(&new2);
	my_string_destroy(&new3);
	my_string_destroy(&new4);
	
	// Push all words from dictionary.txt into generic vectors in an array based on word length, represented by the index.
	GENERIC_VECTOR my_strings[30];
	for (int i = 0; i < 30; i++)
	{
		my_strings[i] = generic_vector_init_default(my_string_init_copy, my_string_destroy);
	}
	FILE* fp = fopen("dictionary.txt", "r");	
	MY_STRING hExtract = my_string_init_default();
	while (my_string_extraction(hExtract, fp) == SUCCESS)
	{
		int index = my_string_get_size(hExtract);
		generic_vector_push_back(my_strings[index], hExtract);
	}
	my_string_destroy(&hExtract);
	fclose(fp);

	// Start game interface
	printf("********************************* LET'S PLAY HANGMAN! *********************************\n");
	printf("Enter your desired word length: ");
	int length;
	int noc = scanf(" %d", &length);
	while (noc != 1 || length <= 1 || length == 23 || (length >= 25 && length <= 27) || length > 29)
	{
		printf("There are no words of that length. Try again: ");
		clear_keyboard_buffer();
		noc = scanf(" %d", &length);
	}
	printf("\nGreat! I'm thinking of a word with %d letters.\n\n", length);
	
	printf("Enter the number of guesses you want: ");
	int guesses;
	noc = scanf(" %d", &guesses);
	while (noc != 1 || guesses < 1)
	{
		printf("You'll need at least one guess! Try again: ");
		clear_keyboard_buffer();
		noc = scanf(" %d", &guesses);
	}
	if (guesses == 1) printf("\nAlright, you have 1 chance to guess my word.\n\n");
	else printf("\nAlright, you have %d chances to guess my word.\n\n", guesses);

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

	Boolean printWordList = (input == 'y' || input == 'Y') ? TRUE : FALSE;

	GENERIC_VECTOR word_list = my_strings[length];
	MY_STRING current_key = my_string_init_default();
	for (int i = 0; i < length; ++i)
	{
		my_string_push_back(current_key, '-');
	}

	Node* root = NULL;

	for (int i = 0; i < 30; i++)
	{
		printf("WORDS OF SIZE %d: %d\n", i, generic_vector_get_size(my_strings[i]));
		//generic_vector_destroy(my_strings + i);
	}

	// **********************************************************************************************

	char guess;
	printf("Guess a letter: ");
	scanf("%c", &guess);
	while (!isalpha(guess))
	{
		clear_keyboard_buffer();
		printf("That's not a letter. Try again: ");
		scanf("%c", &guess);
	}
	clear_keyboard_buffer();
	guess = tolower(guess);
	printf("You guessed %c\n", guess);

	for(int i = 0; i < generic_vector_get_size(current_strings); ++i)
	{
		tree_insert(;
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
