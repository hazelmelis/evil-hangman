#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[])
{
  MY_STRING hString1 = my_string_init_default();
  MY_STRING hString2 = my_string_init_c_string("");
  MY_STRING hString3 = my_string_init_c_string("abracsdgafhdshgartghsgrew");

 
  if (my_string_empty(hString2) == TRUE) printf("string is empty.\n");

  // printf("capacity: %d\n", my_string_get_capacity(hString2));
 
  my_string_push_back(hString2, 'r');
  //printf("capacity: %d\n", my_string_get_capacity(hString2));
  
   my_string_pop_back(hString2);

  if (my_string_empty(hString2) == TRUE) printf("string is empty.\n");

  my_string_push_back(hString2, 'd');
  my_string_push_back(hString2, 'a');
  my_string_push_back(hString2, 'y');

  
  
 

  my_string_push_back(hString1, 'm');
  my_string_push_back(hString1, 'o');
my_string_push_back(hString1, 'n');
 my_string_push_back(hString1, 'k');
 my_string_push_back(hString1, 'e');
 my_string_push_back(hString1, 'y');

 printf("%s\n", my_string_c_str(hString1));

 for (int i = 0; i < 3; i++)
   {
     my_string_pop_back(hString1);
   }

 printf("%s\n", my_string_c_str(hString1));

 if (my_string_at(hString1, 3) == NULL) printf("index out of bounds.\n");

 my_string_concat(hString1, hString2);
 my_string_concat(hString1, hString3);

 printf("%s\n", my_string_c_str(hString1));

 printf("size: %d\n", my_string_get_size(hString1));

 printf("cap: %d\n", my_string_get_capacity(hString1));
 

 my_string_destroy(&hString1);
 my_string_destroy(&hString2);
 my_string_destroy(&hString3);
 
 return 0;
}
