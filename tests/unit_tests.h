#ifndef UNIT_TESTS_HEADER
#define UNIT_TESTS_HEADER


#include <cstddef> //for size_t




#define  COUNT_TESTS(array_tests) (sizeof(array_tests) / sizeof(array_tests[0]))




struct test_info_t
{
    const char *func_name;
    const char *file_name;
};




#define  TEST_INIT  {test_info->func_name = __func__; \
                     test_info->file_name = __FILE__; }



#define RUN_TESTS(tests)    ( run_tests(tests, COUNT_TESTS(tests) ) )



typedef  int (*ptest_func)(struct test_info_t  *test_info);


#define TEST_BROKEN    (-1)
#define TEST_PASSED    (0)





void run_tests(ptest_func *tests, size_t count_tests);






#endif //UNIT_TESTS_HEADER
