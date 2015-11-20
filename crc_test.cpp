#include "unit_tests.h"
#include "universal_crc.h"





int test_crc_type_helper_uint8(struct test_info_t  *test_info)
{

    TEST_INIT;


    if(
        sizeof(CRC_Type_helper< (1-1)/8 >::value_type) != sizeof(uint8_t) ||
        sizeof(CRC_Type_helper< (2-1)/8 >::value_type) != sizeof(uint8_t) ||
        sizeof(CRC_Type_helper< (3-1)/8 >::value_type) != sizeof(uint8_t) ||
        sizeof(CRC_Type_helper< (4-1)/8 >::value_type) != sizeof(uint8_t) ||
        sizeof(CRC_Type_helper< (5-1)/8 >::value_type) != sizeof(uint8_t) ||
        sizeof(CRC_Type_helper< (6-1)/8 >::value_type) != sizeof(uint8_t) ||
        sizeof(CRC_Type_helper< (7-1)/8 >::value_type) != sizeof(uint8_t) ||
        sizeof(CRC_Type_helper< (8-1)/8 >::value_type) != sizeof(uint8_t)
      )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_type_helper_uint16(struct test_info_t  *test_info)
{

    TEST_INIT;


    if(
        sizeof(CRC_Type_helper< (9 -1)/8 >::value_type) != sizeof(uint16_t) ||
        sizeof(CRC_Type_helper< (10-1)/8 >::value_type) != sizeof(uint16_t) ||
        sizeof(CRC_Type_helper< (11-1)/8 >::value_type) != sizeof(uint16_t) ||
        sizeof(CRC_Type_helper< (12-1)/8 >::value_type) != sizeof(uint16_t) ||
        sizeof(CRC_Type_helper< (13-1)/8 >::value_type) != sizeof(uint16_t) ||
        sizeof(CRC_Type_helper< (14-1)/8 >::value_type) != sizeof(uint16_t) ||
        sizeof(CRC_Type_helper< (15-1)/8 >::value_type) != sizeof(uint16_t) ||
        sizeof(CRC_Type_helper< (16-1)/8 >::value_type) != sizeof(uint16_t)
      )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_crc_type_helper_uint32(struct test_info_t  *test_info)
{

    TEST_INIT;


    if(
        sizeof(CRC_Type_helper< (17-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (18-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (19-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (20-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (21-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (22-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (23-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (24-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (25-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (26-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (27-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (28-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (29-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (30-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (31-1)/8 >::value_type) != sizeof(uint32_t) ||
        sizeof(CRC_Type_helper< (32-1)/8 >::value_type) != sizeof(uint32_t)
      )
        return TEST_BROKEN;


    return TEST_PASSED;
}



ptest_func tests[] =
{

    //CRC_Type_Helper
    test_crc_type_helper_uint8,
    test_crc_type_helper_uint16,
    test_crc_type_helper_uint32
};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}
