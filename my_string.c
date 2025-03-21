#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include "my_string.h"

struct my_string
{
  int size;
  int capacity;
  char* data;
};

typedef struct my_string My_string;

MY_STRING my_string_init_default(void)
{
  My_string* pMy_string = (My_string*)malloc(sizeof(My_string));
  if (pMy_string == NULL)
    {
      return NULL;
    }
  
    pMy_string->size = 0;
    pMy_string->capacity = 7;
    
    pMy_string->data = (char*)malloc(sizeof(char)*pMy_string->capacity);
    if (pMy_string->data == NULL)
      {
        free(pMy_string);
	return NULL;
      }
    
    return (MY_STRING)pMy_string;

}

MY_STRING my_string_init_c_string(const char* c_string)
{
  My_string* pMy_string = (My_string*)malloc(sizeof(My_string));

  if (pMy_string == NULL)
  {
    return NULL;
  }
  
  pMy_string->size = 0;
  int i = 0;

    while (c_string[i] != '\0')
      {
	pMy_string->size++;
	i++;
      }

    pMy_string->capacity = pMy_string->size + 1;

    pMy_string->data = (char*)malloc(sizeof(char)*(pMy_string->capacity));
       if (pMy_string->data == NULL)
	 {
	   free(pMy_string);
	   return NULL;
	 }

       i = 0;
    while (c_string[i] != '\0')
	{
	   pMy_string->data[i] = c_string[i];
	   i++;
	}
  
  return (MY_STRING)pMy_string;

}

void my_string_destroy(MY_STRING* phMy_string)
{
  My_string* pMy_string = (My_string*)*(phMy_string);
  free(pMy_string->data); pMy_string->data = NULL;
  free(pMy_string); *phMy_string = NULL;
}

int my_string_get_capacity(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string; 
  return pMy_string->capacity;

}

int my_string_get_size(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;
  return pMy_string->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
  My_string* pLeft_string = (My_string*)hLeft_string;
  My_string* pRight_string = (My_string*)hRight_string;

  int i = 0;
  int left = 0;
  int right = 0;

  while (i < pLeft_string->size && i < pRight_string->size && pLeft_string->data[i] == pRight_string->data[i])
    {
      i++;
      left = pLeft_string->data[i];
      right = pRight_string->data[i];
    }

  return left - right;
}
		    
Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
  My_string* pMy_string = (My_string*)hMy_string;
    
  if (fp == NULL)
    {
      printf("Failed to open dictionary file for reading.\n");
      return FAILURE;
    }

  char c;
  int noc = fscanf(fp, " %c", &c);
  if (noc != 1) return FAILURE;

  pMy_string->size = 0;
  int i = 0;
 
  while (!isspace(c) && !feof(fp))
  {
    if (i + 1 >= pMy_string->capacity)
      {
	char* temp = realloc(pMy_string->data, pMy_string->capacity + 1);
	if (temp == NULL) return FAILURE;
	pMy_string->data = temp;
	pMy_string->capacity++;
      }
    pMy_string->data[i] = c;
    pMy_string->size++;
    i++;
    noc = fscanf(fp, "%c", &c);
  }

  ungetc(c, fp);

  return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
  My_string* pMy_string = (My_string*)hMy_string;

  if (fp == NULL)
    {
      printf("Failed to open file for writing.\n");
      return FAILURE;
    }

  int i = 0;
  char c = pMy_string->data[i];

  while (i < pMy_string->size)
    {
      fprintf(fp, "%c", c);
      i++;
      c = pMy_string->data[i];
    }

  return SUCCESS;
}

Status my_string_push_back(MY_STRING hMy_string, char item)
{
  My_string* pMy_string = (My_string*)hMy_string;
  
  if (pMy_string->size + 1 >= pMy_string->capacity)
    {
      char* temp = realloc(pMy_string->data, pMy_string->capacity * 2);
      if (temp == NULL) return FAILURE;
      pMy_string->data = temp;
      pMy_string->capacity *= 2;
    }

  pMy_string->data[pMy_string->size] = item;
  pMy_string->size++;

  return SUCCESS;
}

Status my_string_pop_back(MY_STRING hMy_string)
{
  if (my_string_get_size(hMy_string) == 0) return FAILURE;
  
  My_string* pMy_string = (My_string*)hMy_string;

  pMy_string->size--;

  return SUCCESS;
}

char* my_string_at(MY_STRING hMy_string, int index)
{
  My_string* pMy_string = (My_string*)hMy_string;

  if (index >= pMy_string->size) return NULL;
  
  return pMy_string->data + index;
}

char* my_string_c_str(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;

  pMy_string->data[pMy_string->size] = '\0';
  
  return pMy_string->data;
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
  My_string* pResult = (My_string*)hResult;
  My_string* pAppend = (My_string*)hAppend;
  
  if (my_string_get_capacity(hResult) <= my_string_get_size(hAppend))
    {
      char* temp = realloc(pResult->data, pResult->capacity + pAppend->size);
      if (temp == NULL) return FAILURE;
      pResult->data = temp; 
      pResult->capacity += pAppend->size;
    }

  int i = pResult->size; int j = 0;
  while (j < pAppend->size)
    {
      pResult->data[i] = pAppend->data[j];
      pResult->size++;
      i++; j++;
    }
  
  
  return SUCCESS;
  
}

Boolean my_string_empty(MY_STRING hMy_string)
{
  My_string* pMy_string = (My_string*)hMy_string;
  return (pMy_string->size == 0)?TRUE:FALSE;

}

Status my_string_assignment(MY_STRING hLeft, MY_STRING hRight)
{
	My_string* pLeft = (My_string*)hLeft;
	My_string* pRight = (My_string*)hRight;

	char* temp_data = (char*)malloc(sizeof(char) * pLeft->capacity);
	if (temp_data == NULL) return FAILURE;
	int temp_size = 0;
	int temp_capacity = pLeft->capacity;

	for (int i = 0; i < pRight->size; i++)
	{		
		if (temp_capacity - 1 <= i)
		{
			char* temp_data1 = (char*)realloc(temp_data, temp_capacity * 2);
			if (temp_data1 == NULL) 
			{
				free(temp_data);
				return FAILURE;
			}
			temp_capacity *= 2;
		}

		temp_data[i] = *(my_string_at(hRight, i));
		temp_size++;
	}
	
	free(pLeft->data);
	pLeft->size = temp_size;
	pLeft->capacity = temp_capacity;
	pLeft->data = temp_data;

	pRight->data[2] = 'W';

	return SUCCESS;
}

MY_STRING my_string_init_copy(MY_STRING hMy_string)
{
	MY_STRING hCopy = my_string_init_default();
	if (hCopy == NULL) return FAILURE;

	if (my_string_assignment(hCopy, hMy_string) == FAILURE)
	{
		return NULL;
	}
	return hCopy;

}
