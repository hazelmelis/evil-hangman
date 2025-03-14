
#ifndef UNIT_TEST_H
#define UNIT_TEST_H
#include "my_string.h"

Status test_init_default_returns_nonNULL(char* buffer, int length);
Status test_get_size_on_init_default_returns_0(char* buffer, int length);
Status test_herkmen_init_default_cap_7(char* buffer, int length);
Status test_herkmen_destroy_fixes_dangling_pointer(char* buffer, int length);
Status test_herkmen_init_c_string_size(char* buffer, int length);
Status test_herkmen_my_string_at_out_of_bounds(char* buffer, int length);
Status test_herkmen_my_string_compare_returns0(char* buffer, int length);
Status test_herkmen_my_string_compare_returns0_2(char* buffer, int length);
Status test_herkmen_extraction_whitespace(char* buffer, int length);
Status test_herkmen_extraction_size(char* buffer, int length);
Status test_herkmen_extraction_capacity(char* buffer, int length);
Status test_herkmen_extraction_eof(char* buffer, int length);
Status test_herkmen_insertion_string(char* buffer, int length);
Status test_herkmen_pushback_success(char* buffer, int length);
Status test_herkmen_pushback_resize(char* buffer, int length);
Status test_herkmen_popback_empty(char* buffer, int length);
Status test_herkmen_popback_empty1(char* buffer, int length);
Status test_herkmen_popback_cap(char* buffer, int length);
Status test_herkmen_myStringAt_inBounds(char* buffer, int length);
Status test_herkmen_myStringAt_outOfBounds(char* buffer, int length);
Status test_herkmen_myStringAt_outOfBounds1(char* buffer, int length);
Status test_herkmen_c_str(char* buffer, int length);
Status test_herkmen_c_str_size(char* buffer, int length);
Status test_herkmen_concat_size(char* buffer, int length);
Status test_herkmen_empty(char* buffer, int length);

#endif
