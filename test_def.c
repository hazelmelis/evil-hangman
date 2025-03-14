#include <stdio.h>
#include <stdlib.h>
#include "unit_test.h"
#include <string.h>

Status test_init_default_returns_nonNULL(char* buffer, int length)
{
 MY_STRING hString = NULL;
 hString = my_string_init_default();
 if(hString == NULL)
 {
 strncpy(buffer, "test_init_default_returns_nonNULL\n"
 "my_string_init_default returns NULL", length);
 return FAILURE;
 }
 else
 {
 my_string_destroy(&hString);
 strncpy(buffer, "\ttest_init_default_returns_nonNULL\n", length);
 return SUCCESS;
 }
}

Status test_get_size_on_init_default_returns_0(char* buffer, int length)
{
 MY_STRING hString = NULL;
 Status status;
 hString = my_string_init_default();
 if(my_string_get_size(hString) != 0)
 {
 status = FAILURE;
 printf("Expected a size of 0 but got %d\n", my_string_get_size(hString));
 strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
 "Did not receive 0 from get_size after init_default\n", length);
 }
 else
 {
 status = SUCCESS;
 strncpy(buffer, "test_get_size_on_init_default_returns_0\n"
 , length);
 }
 my_string_destroy(&hString);
 return status;
}

Status test_herkmen_init_default_cap_7(char* buffer, int length)
{
  MY_STRING hString = NULL;
  Status status;
  hString = my_string_init_default();
  if (my_string_get_capacity(hString) != 7)
    {
      status = FAILURE;
      printf("Expected a capacity of 7 but got %d\n", my_string_get_capacity(hString));
      strncpy(buffer, "test_herkmen_init_default_cap_7\n"
	      "Did not receive 7 from get_capacity  after init_default\n", length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_herkment_init_default_cap_7\n", length);
    }
  my_string_destroy(&hString);
  return status;
}

Status test_herkmen_destroy_fixes_dangling_pointer(char* buffer, int length)
{
  MY_STRING hString = NULL;
  hString = my_string_init_default();
  my_string_destroy(&hString);

  if (hString != NULL)
    {
      strncpy(buffer, "test_herkmen_destroy_fixes_dangling_pointer\n"
	      "my_string_destroy leaves dangling pointer\n", length);
      return FAILURE;
    }
  else
    {
      strncpy(buffer, "test_herkmen_destroy_fixes_dangling_pointer\n", length);
      return SUCCESS;
    }
}

Status test_herkmen_init_c_string_size(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("fred");
  Status status;
  if (my_string_get_size(hString) != 4)
    {
      status = FAILURE;
      printf("Expected a size of 4 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_herkmen_init_c_string_size\n"
	      "Did not receive 4 from get_size after init_c_string with 'fred'\n", length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_herkmen_init_c_string_size\n", length);
    }

  my_string_destroy(&hString);
  return status;

}

Status test_herkmen_my_string_at_out_of_bounds(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("freddy");
  Status status;
  
  if (my_string_at(hString, my_string_get_size(hString)) != NULL)
    {
      status = FAILURE;
      strncpy(buffer, "test_herkmen_my_string_at_out_of_bounds\n"
	      "Did not receive NULL from my_string_at index get_size\n", length);
    }
    else
      {
	status = SUCCESS;
	strncpy(buffer, "test_herkmen_my_string_at_out_of_bounds\n", length);
      }

    my_string_destroy(&hString);
    return status;
}

Status test_herkmen_my_string_compare_returns0(char* buffer, int length)
{
  MY_STRING hLeft = my_string_init_c_string("aaaaaaaaaple");
  MY_STRING hRight = my_string_init_c_string("aaaaaaaaaple");
  Status status;

  if (my_string_compare(hLeft, hRight) != 0)
    {
      status = FAILURE;
      printf("Expected 0 but got %d\n", my_string_compare(hLeft, hRight));
      strncpy(buffer, "test_herkmen_my_string_compare_returns0\n"
	      "my_string_compare does not return 0 when both compared strings 'aaaaaaaaaple'\n", length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_herkmen_my_string_compare_returns0\n", length);
    }

  my_string_destroy(&hLeft);
  my_string_destroy(&hRight);
  return status;
}

Status test_herkmen_my_string_compare_returns0_2(char* buffer, int length)
{
  MY_STRING hLeft = my_string_init_default();
  MY_STRING hRight = my_string_init_default();
  Status status;

  if (my_string_compare(hLeft, hRight) != 0)
    {
      status = FAILURE;
      printf("Expected 0 but got %d\n", my_string_compare(hLeft, hRight));
      strncpy(buffer, "test_herkmen_my_string_compare_returns0_2\n"
	      "my_string_compare does not return 0 when both strings are from init_default\n", length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_herkmen_my_string_compare_returns0_2\n", length);
    }

  my_string_destroy(&hLeft);
  my_string_destroy(&hRight);
  return status;

}

Status test_herkmen_extraction_whitespace(char* buffer, int length)
{
  MY_STRING hString = my_string_init_default();
  Status status;

  FILE* fp = fopen("test_extraction.txt", "r");
  
  my_string_extraction(hString, fp);

  if (my_string_get_size(hString) != 6)
    {
      status = FAILURE;
      printf("Expected size of 6 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_herkmen_extraction_whitespace\n"
	      "Did not receive correct size after extracting string with leading whitespaces\n", length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_herkmen_extraction_whitespace\n", length);
    }

  fclose(fp);
  my_string_destroy(&hString);
  return status;
}

Status test_herkmen_extraction_size(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("bananas");
  Status status;

  FILE* fp = fopen("test_extraction.txt", "r");

  my_string_extraction(hString, fp);

  if (my_string_get_size(hString) != 6)
    {
      status = FAILURE;
      printf("Expected size 6 but got %d\n", my_string_get_size(hString));
      strncpy(buffer, "test_herkmen_extraction_size\n"
	      "Did not shrink size to 6 after extraction with initial size 7\n", length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_herkmen_extraction_size\n", length);
    }

  fclose(fp);
  my_string_destroy(&hString);
  return status;
}

Status test_herkmen_extraction_capacity(char* buffer, int length)
{
  MY_STRING hString = my_string_init_c_string("yellow bananas");
  Status status;

  FILE* fp = fopen("test_extraction.txt", "r");

  my_string_extraction(hString, fp);

  if (my_string_get_capacity(hString) != 15)
    {
      status = FAILURE;
      printf("Expected capacity of 15 but got %d\n", my_string_get_capacity(hString));
      strncpy(buffer, "test_herkmen_extraction_capacity\n"
	      "Did not receive original capacity after extracting a string shorter than the initial\n", length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_herkmen_extraction_capacity\n", length);
    }

  fclose(fp);
  my_string_destroy(&hString);
  return status;
}

Status test_herkmen_extraction_eof(char* buffer, int length)
{
  MY_STRING hString = my_string_init_default();
  Status status;

  FILE* fp = fopen("test_extraction.txt", "r");
  
  while (my_string_extraction(hString, fp) == SUCCESS)

  if (my_string_at(hString, 0) == NULL || *(my_string_at(hString, 0)) != 'k')
    {
      status = FAILURE;
      strncpy(buffer, "test_herkmen_extraction_eof\n"
	      "Did not keep the last extracted string when my_string_extraction failed at the end of test_extraction.txt\n", length);
    }
  else
    {
      status = SUCCESS;
      strncpy(buffer, "test_herkmen_extraction_eof\n", length);
    }

  fclose(fp);
  my_string_destroy(&hString);
  return status;
}

Status test_herkmen_insertion_string(char* buffer, int length)
{
	MY_STRING hString = my_string_init_c_string("Luke Skywalker");
	FILE* fp = fopen("test_extraction.txt", "r");
	Status status;

	my_string_extraction(hString, fp);
  
	FILE* fp1 = fopen("test_insertion.txt", "w");

	my_string_insertion(hString, fp1); 

	char c;
	int noc = fscanf(fp1, "%c", &c);

	while (noc == 1)
	{
		my_string_push_back(hString, c);
		noc = fscanf(fp1, "%c", &c);
	}
	my_string_push_back(hString, c);

	MY_STRING hString1 = my_string_init_c_string("that's");

	if (my_string_compare(hString, hString1) != 0)
	{
		printf("Expected string ~that's~ but got ~%s~", my_string_c_str(hString)); 
		status = FAILURE;
		strncpy(buffer, "test_herkmen_insertion_string\n"
				"Did not successfully insert first string from test_extraction.txt to test_insertion.txt\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_insertion_string\n", length);
	}

	fclose(fp);
	fclose(fp1);
	my_string_destroy(&hString);
	my_string_destroy(&hString1);

	return status;
}

Status test_herkmen_pushback_success(char* buffer, int length)
{
	MY_STRING hString = my_string_init_c_string("Monkey");
	Status status;

	if (my_string_push_back(hString, 's') == FAILURE)
	{
		status = FAILURE;
		strncpy(buffer, "test_herkmen_pushback_success\n"
				"Failed to push back character 's' on initial string 'Monkey'\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_pushback_success\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_herkmen_pushback_resize(char* buffer, int length)
{
	MY_STRING hString = my_string_init_c_string("Yoda");
	Status status;

	my_string_push_back(hString, '.');

	if (my_string_get_size(hString) != 5)
	{
		status = FAILURE;
		printf("Expected size of 5 but got %d\n", my_string_get_size(hString));
		strncpy(buffer, "test_herkmen_pushback_resize\n"
				"Did not receive correct updated size after push back\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_pushback_resize\n", length);
	}

	my_string_destroy(&hString);
	return status;

}

Status test_herkmen_popback_empty(char* buffer, int length)
{
	MY_STRING hString = my_string_init_default();
	Status status;

	if (my_string_pop_back(hString) != FAILURE)
	{
		status = FAILURE;
		strncpy(buffer, "test_herkmen_popback_empty\n"
				"Did not fail on pop back of empty string after init default\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_popback_empty\n", length);
	}

	my_string_destroy(&hString);
	return status;
}

Status test_herkmen_popback_empty1(char* buffer, int length)
{
	MY_STRING hString = my_string_init_c_string("");
	Status status;

	if (my_string_pop_back(hString) != FAILURE)
	{
		status = FAILURE;
		strncpy(buffer, "test_herkmen_popback_empty1\n"
				"Did not fail on pop back after init c string with empty string\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_popback_empty1\n", length);
	}

	my_string_destroy(&hString);
	return status;
}


Status test_herkmen_popback_cap(char* buffer, int length)
{
	MY_STRING hString = my_string_init_c_string("Monkeys");
	my_string_pop_back(hString);
	Status status;

	if (my_string_get_capacity(hString) != 8)
	{
		status = FAILURE;
		printf("Expected capacity of 8 but got %d\n", my_string_get_capacity(hString));
		strncpy(buffer, "test_herkmen_popback_cap\n"
			"Did not maintain the same capacity after pop back on init c-string 'Monkeys'\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_popback_cap\n", length);
	}

	my_string_destroy(&hString);
	return status;

}

Status test_herkmen_myStringAt_inBounds(char* buffer, int length)
{
	MY_STRING hS = my_string_init_c_string("Wyoming");
	Status status;

	if (my_string_at(hS, 6) == NULL || *(my_string_at(hS, 6)) != 'g')
	{
		status = FAILURE;
		strncpy(buffer, "test_herkmen_myStringAt_inBounds\n"
				"Did not receive character 'g' using my_string_at with string 'Wyoming' at index 6\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_myStringAt_inBounds\n", length);
	}

	my_string_destroy(&hS);
	return status;
	
}

Status test_herkmen_myStringAt_outOfBounds(char* buffer, int length)
{
	MY_STRING hS = my_string_init_c_string("Batman");
	Status status;

	if (my_string_at(hS, 6) != NULL)
	{
		status = FAILURE;
		strncpy(buffer, "test_herkmen_myStringAt_outOfBounds\n"
				"Did not receive NULL for out of bounds using my_string_at with string 'Batman' at index 6\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_myStringAt_outOfBounds\n", length);
	}
	
	my_string_destroy(&hS);
	return status;

}

Status test_herkmen_myStringAt_outOfBounds1(char* buffer, int length)
{
	MY_STRING hS = my_string_init_c_string("");
	Status status;

	if (my_string_at(hS, 0) != NULL)
	{
		status = FAILURE;
		strncpy(buffer, "test_herkmen_myStringAt_outOfBounds1\n"
				"Did not receive NULL for out of bounds using my_string_at with init empty c-string at index 0\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_myStringAt_outOfBounds1\n", length);
	}

	my_string_destroy(&hS);
	return status;
}

Status test_herkmen_c_str(char* buffer, int length)
{
	MY_STRING hS = my_string_init_c_string("Bowser");
	char* TestString = my_string_c_str(hS);
	char CompareString[] = "Bowser";
	Status status;

	if (strcoll(CompareString, TestString) != 0)
	{
		status = FAILURE;
		printf("Expected 0 when lexicographically compared with 'Bowser' c-string, but instead got %d\n", strcoll(CompareString, TestString));
		strncpy(buffer, "test_herkmen_c_str\n"
				"Did not receive full null terminated c-string after using my_string_c_str on string object containing 'Bowser'\n",
				length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_c_str\n", length);
	}

	my_string_destroy(&hS);
	return status;

}

Status test_herkmen_c_str_size(char* buffer, int length)
{
	MY_STRING hS = my_string_init_c_string(".");
	my_string_c_str(hS);
	Status status;

	if (my_string_get_size(hS) != 1)
	{
		status = FAILURE;
		printf("Expected size 1 but got %d\n", my_string_get_size(hS));
		strncpy(buffer, "test_herkmen_c_str_size\n"
				"Did not keep the same size after using my_string_c_str\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_c_str_size\n", length);
	}

	my_string_destroy(&hS);
	return status;
}

Status test_herkmen_concat_size(char* buffer, int length)
{
	MY_STRING hS = my_string_init_c_string("Tiger");
	MY_STRING hAppend = my_string_init_c_string(" Woods");
	Status status;

	my_string_concat(hS, hAppend);

	if (my_string_get_size(hS) != 11)
	{
		status = FAILURE;
		printf("Expected size 11 but got %d\n", my_string_get_size(hS));
		strncpy(buffer, "test_herkmen_concat_size\n"
				"Did not receive corrected update size after concat 'Tiger' and ' Woods'\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_concat_size\n", length);
	}

	my_string_destroy(&hS);
	my_string_destroy(&hAppend);
	return status;
}

Status test_herkmen_empty(char* buffer, int length)
{
	MY_STRING hS = my_string_init_c_string("");
	MY_STRING hAppend = my_string_init_c_string("");
	Status status;

	my_string_concat(hS, hAppend);

	if (my_string_empty(hS) == FALSE)
	{
		status = FAILURE;
		strncpy(buffer, "test_herkmen_empty\n"
				"Received false negative from my_string_empty\n", length);
	}
	else
	{
		status = SUCCESS;
		strncpy(buffer, "test_herkmen_empty\n", length);
	}

	my_string_destroy(&hS);
	my_string_destroy(&hAppend);
	return status;
}
