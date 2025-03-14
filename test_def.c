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
  if (fp == NULL)
    {
      printf("Failed to open test_extraction.txt for reading.\n");
      my_string_destroy(&hString);
      return FAILURE;
    }
  
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

  if (fp == NULL)
    {
      printf("Failed to open test_extraction.txt for reading.\n");
      my_string_destroy(&hString);
      return FAILURE;
    }
  
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
  if (fp == NULL)
    {
      printf("Failed to open test_extraction.txt for reading.\n");
      my_string_destroy(&hString);
      return FAILURE;
    }

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
  
  if (fp == NULL)
    {
      printf("Failed to open test_extraction.txt for reading.\n");
      my_string_destroy(&hString);
      return FAILURE;
    }

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
