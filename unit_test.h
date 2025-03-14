
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

#endif
