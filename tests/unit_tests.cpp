#include <stdio.h>
#include <stdlib.h> //for exit



#include "unit_tests.h"





void run_tests(ptest_func *tests, size_t count_tests)
{
    struct test_info_t test_info;
    unsigned int i;

    for(i=0; i < count_tests; ++i)
    {

        if( tests[i](&test_info) == TEST_BROKEN)
        {
            printf("test:  %s  in file: %s  is broken\n", test_info.func_name, test_info.file_name);
            exit(1);
        }
    }


    printf("all test passed  count tests = %zd\n", count_tests);
}

