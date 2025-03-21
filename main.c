#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
int main(int argc, char* argv[])
{
  MY_STRING hString2 = my_string_init_c_string("Monkey see monkey do");

MY_STRING hString1 = NULL; 
  hString1 = my_string_init_copy(hString2);
 printf("%s\n", my_string_c_str(hString2));
 printf("%s\n", my_string_c_str(hString1));

 printf("size: %d\n", my_string_get_size(hString1));

 printf("cap: %d\n", my_string_get_capacity(hString1));

 printf("%s\n", my_string_c_str(hString2));
 

 my_string_destroy(&hString1);
 my_string_destroy(&hString2);
 
 return 0;
}
