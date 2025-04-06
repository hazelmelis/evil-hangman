#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include "generic_vector.h"

void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{
	// Push all words from dictionary.txt into generic vectors in an array based on word length, represented by the index.
	GENERIC_VECTOR a[30];
	for (int i = 0; i < 30; i++)
	{
		a[i] = generic_vector_init_default(my_string_init_copy, my_string_destroy);
	}
	FILE* fp = fopen("dictionary.txt", "r");	
	MY_STRING hExtract = my_string_init_default();
	while (my_string_extraction(hExtract, fp) == SUCCESS)
	{
		int index = my_string_get_size(hExtract);
		generic_vector_push_back(a[index], hExtract);
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
	Boolean printWordList = (input == 'y' || input == 'Y') ? TRUE : FALSE;
	(printWordList == TRUE) ? printf("True") : printf("False");


	GENERIC_VECTOR hGameVector = a[length];

	for (int i = 0; i < 30; ++i)
	{
	//	printf("WORDS OF SIZE %d: %d\n", i, generic_vector_get_size(a[i]));
		generic_vector_destroy(a + i);
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
