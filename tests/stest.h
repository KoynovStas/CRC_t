/*
 * stest.h
 *
 *
 * version 1.0
 *
 *
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2017, Koynov Stas - skojnov@yandex.ru
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
 * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef STEST_HEADER
#define STEST_HEADER


#include <stdio.h>  //printf





enum test_status_t
{
    STATUS_PASS,
    STATUS_SKIP,
    STATUS_FAIL
};



struct test_info_t
{
    const char *file_name;
    const char *func_name;
    int         line_num;

    int         status;

    const char *msg;
};



#define TEST(name) static struct test_info_t name(void *data)



static inline struct test_info_t get_test_info( const char *file_name,
                                                const char *func_name,
                                                int         line_num,
                                                int         status,
                                                const char *msg)
{
    struct test_info_t test_info = {file_name, func_name, line_num, status, msg};
    return test_info;
}


#define TEST_PASS(msg)  return get_test_info(__FILE__, __func__, __LINE__, STATUS_PASS, msg)
#define TEST_SKIP(msg)  return get_test_info(__FILE__, __func__, __LINE__, STATUS_SKIP, msg)
#define TEST_FAIL(msg)  return get_test_info(__FILE__, __func__, __LINE__, STATUS_FAIL, msg)



#define TEST_ASSERT2(expr, msg)  if( !(expr) ) TEST_FAIL(msg)
#define TEST_ASSERT(expr)  TEST_ASSERT2(expr, NULL)


/*
 * For GCC 4.6 or higher, in C++ you can use a standard right static_assert(exp, msg)
 * in *.c and in *.h files.
 * For GCC 4.6 is required to add CFLAGS += -std="c++0x"
 * Simple C (gcc) have not static_assert.
 * A lot of variants, it is the most simple and intuitive
 * It can be used in *.c and in *.h files.
 * (macros that use function style can be used in *.c files only)
 *
 * Disadvantages: you can not be set msg to display the console when compiling
 *
 * Example:
 *
 * TEST_STATIC_ASSERT( sizeof(char) == 1)  //good job
 * TEST_STATIC_ASSERT( sizeof(char) != 1)  //You will get a compilation error
*/
#define TEST_ASSERT_CONCAT_(a, b) a##b
#define TEST_ASSERT_CONCAT(a, b) TEST_ASSERT_CONCAT_(a, b)
#define TEST_STATIC_ASSERT(expr) \
    enum { TEST_ASSERT_CONCAT(assert_line_, __LINE__) = 1/(int)(!!(expr)) }



typedef  struct test_info_t (*ptest_func)(void *data);


struct test_case_t;

typedef  void  (*pinit_func)(struct test_case_t *test_case);
typedef  void  (*pclean_func)(struct test_case_t *test_case);



struct test_case_t
{
    const char *file_name;
    const char *case_name;
    int         line_num;
    size_t      count_tests;

    ptest_func *tests;

    void       *data;

    pinit_func  init;
    pclean_func clean;


    //private
    size_t count_pass;
    size_t count_skip;
    size_t count_fail;
};



#define  SIZE_OF_ARRAY(array) (sizeof(array) / sizeof(array[0]))


#define TEST_CASE(_name, _tests, _data, _init, _clean) \
    struct test_case_t _name = {                       \
    __FILE__, #_name, __LINE__,                        \
    SIZE_OF_ARRAY(_tests), _tests,                     \
   _data, _init, _clean, 0, 0, 0 };



static void print_header(const char *title)
{
    printf("\n\n---------- Start testing");

    if(title)
        printf(" of %s", title);

    printf(" ----------");
}



static void print_footer(const char *title)
{
    printf("========== Finished testing");

    if(title)
        printf(" of %s", title);

    printf(" ==========\n");
}



#define TEXT_PASS "\nPASS: "
#define TEXT_SKIP "\nSKIP: "
#define TEXT_FAIL "\nFAIL: "

#define TEXT_PASSED "passed"
#define TEXT_SKIPED "skipped"
#define TEXT_FAILED "failed\n"



#ifdef WITHOUT_CONSOLE_COLOR

    #define COLOR_TEXT_PASS  TEXT_PASS
    #define COLOR_TEXT_SKIP  TEXT_SKIP
    #define COLOR_TEXT_FAIL  TEXT_FAIL

    #define COLOR_TEXT_PASSED  TEXT_PASSED
    #define COLOR_TEXT_SKIPED  TEXT_SKIPED
    #define COLOR_TEXT_FAILED  TEXT_FAILED

#else

    #define COLOR_TEXT_NORMAL "\033[0m"
    #define COLOR_TEXT_RED    "\033[31m"
    #define COLOR_TEXT_GREEN  "\033[32m"
    #define COLOR_TEXT_YELLOW "\033[33m"

    #define COLOR_TEXT_PASS COLOR_TEXT_GREEN   TEXT_PASS  COLOR_TEXT_NORMAL
    #define COLOR_TEXT_SKIP COLOR_TEXT_YELLOW  TEXT_SKIP  COLOR_TEXT_NORMAL
    #define COLOR_TEXT_FAIL COLOR_TEXT_RED     TEXT_FAIL  COLOR_TEXT_NORMAL

    #define COLOR_TEXT_PASSED COLOR_TEXT_GREEN   TEXT_PASSED  COLOR_TEXT_NORMAL
    #define COLOR_TEXT_SKIPED COLOR_TEXT_YELLOW  TEXT_SKIPED  COLOR_TEXT_NORMAL
    #define COLOR_TEXT_FAILED COLOR_TEXT_RED     TEXT_FAILED  COLOR_TEXT_NORMAL

#endif



static void print_status(struct test_case_t *test_case, struct test_info_t *test_info)
{
    switch (test_info->status)
    {
        case STATUS_PASS:
            printf(COLOR_TEXT_PASS "  %s", test_info->func_name);
            test_case->count_pass++;
            break;

        case STATUS_SKIP:
            printf(COLOR_TEXT_SKIP "  %s", test_info->func_name);
            test_case->count_skip++;
            break;

        default:
            printf(COLOR_TEXT_FAIL "  %s  in file: %s:%d", test_info->func_name, test_info->file_name, test_info->line_num);
            test_case->count_fail++;
            break;
    }


    if(test_info->msg)
        printf("  msg:  %s", test_info->msg);
}



static void print_total(size_t count_pass, size_t count_skip, size_t count_fail)
{
    printf("\n\nTotals:");


    if(count_pass)
        printf(" %zu " COLOR_TEXT_PASSED, count_pass);
    else
        printf(" %zu " TEXT_PASSED, count_pass);


    if(count_skip)
        printf(", %zu " COLOR_TEXT_SKIPED, count_skip);
    else
        printf(", %zu " TEXT_SKIPED, count_skip);


    if(count_fail)
        printf(", %zu " COLOR_TEXT_FAILED, count_fail);
    else
        printf(", %zu " TEXT_FAILED, count_fail);
}



static int run_case(struct test_case_t *test_case)
{
    struct test_info_t test_info;
    size_t i;


    print_header(test_case->case_name);


    for(i = 0; i < test_case->count_tests; ++i)
    {
        if( test_case->init )
            test_case->init(test_case);


        test_info = test_case->tests[i](test_case->data); //run test


        if( test_case->clean )
            test_case->clean(test_case);


        print_status(test_case, &test_info);
    }


    print_total(test_case->count_pass, test_case->count_skip, test_case->count_fail);
    print_footer(test_case->case_name);

    return test_case->count_fail;
}



static inline int run_cases(struct test_case_t *test_cases[], size_t count_cases)
{
    size_t i;
    size_t count_pass = 0, count_skip = 0, count_fail = 0;


    for(i = 0; i < count_cases; ++i)
    {
       count_fail += run_case(test_cases[i]);

       count_pass += test_cases[i]->count_pass;
       count_skip += test_cases[i]->count_skip;
    }

    if( count_cases > 1 )
    {
        print_total(count_pass, count_skip, count_fail);
        print_footer(NULL);
    }

    return count_fail;
}



#define MAIN_CASE(test_case) int main(void) { return run_case(&test_case); }

#define MAIN_CASES(test_cases) int main(void) { return run_cases(test_cases, SIZE_OF_ARRAY(test_cases)); }

#define MAIN_TESTS(tests)                             \
    struct test_case_t test_case = {                  \
    NULL, NULL, 0, SIZE_OF_ARRAY(tests), tests, NULL};\
    MAIN_CASE(test_case)





#endif //STEST_HEADER
