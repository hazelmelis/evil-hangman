#include <stdio.h>
#include "unit_test.h"

int main(int argc, char* argv[])
{
 Status (*tests[])(char*, int) =
 {
 test_init_default_returns_nonNULL,
 test_get_size_on_init_default_returns_0,
 test_herkmen_init_default_cap_7,
 test_herkmen_destroy_fixes_dangling_pointer,
 test_herkmen_init_c_string_size,
 test_herkmen_my_string_at_out_of_bounds,
 test_herkmen_my_string_compare_returns0,
 test_herkmen_my_string_compare_returns0_2,
 test_herkmen_extraction_whitespace,
 test_herkmen_extraction_size,
 test_herkmen_extraction_capacity,
 test_herkmen_extraction_eof,
 };
 int number_of_functions = sizeof(tests) / sizeof(tests[0]);
 int i;
 char buffer[500];
 int success_count = 0;
 int failure_count = 0;
 for(i=0; i<number_of_functions; i++)
 {
 if(tests[i](buffer, 500) == FAILURE)
 {
 printf("FAILED: Test %d failed miserably\n", i);
 printf("\t%s\n", buffer);
 failure_count++;
 }
 else
 {
   printf("PASS: Test %d passed\n", i);
   printf("\t%s\n", buffer);
 success_count++;
 }
 }
 printf("Total number of tests: %d\n", number_of_functions);
 printf("%d/%d Pass, %d/%d Failure\n", success_count,
 number_of_functions, failure_count, number_of_functions);
 return 0;
}
