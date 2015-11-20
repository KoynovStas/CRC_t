#include "unit_tests.h"
#include "universal_crc.h"




//------------- tests for CRC_Type_helper -------------



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



int test_crc_type_helper_uint64(struct test_info_t  *test_info)
{

    TEST_INIT;


    //Template CRC_Type_helper default is uint64_t
    if( sizeof(CRC_Type_helper<100>::value_type) != sizeof(uint64_t) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//------------- tests for Universal_CRC methods -------------



int test_universal_crc_name(struct test_info_t  *test_info)
{

    TEST_INIT;


    Universal_CRC<1, 0, 0, true, true, 0>  ucrc;


    if( ucrc.name != "" )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_name_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    const char* name = "some_name";

    Universal_CRC<1, 0, 0, true, true, 0>  ucrc(name);


    if( ucrc.name != name )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_bits(struct test_info_t  *test_info)
{

    TEST_INIT;

    Universal_CRC<1, 0, 0, true, true, 0>  ucrc_1;


    if( ucrc_1.get_bits() != 1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_poly(struct test_info_t  *test_info)
{

    TEST_INIT;

    Universal_CRC<16, 1234, 0, true, true, 0>  ucrc;


    if( ucrc.get_poly() != 1234 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_init(struct test_info_t  *test_info)
{

    TEST_INIT;

    Universal_CRC<16, 0, 1234, true, true, 0>  ucrc;


    if( ucrc.get_init() != 1234 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_xor_out(struct test_info_t  *test_info)
{

    TEST_INIT;

    Universal_CRC<16, 0, 0, true, false, 4321>  ucrc;


    if( ucrc.get_xor_out() != 4321 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_ref_in(struct test_info_t  *test_info)
{

    TEST_INIT;

    Universal_CRC<16, 0, 0, true, false, 4321>  ucrc;


    if( ucrc.get_ref_in() != true )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_ref_out(struct test_info_t  *test_info)
{

    TEST_INIT;

    Universal_CRC<16, 0, 0, true, false, 4321>  ucrc;


    if( ucrc.get_ref_out() != false )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_crc_init(struct test_info_t  *test_info)
{

    TEST_INIT;

    Universal_CRC<16, 0, 0x1234, false, false, 0>  ucrc;


    if( ucrc.get_crc_init() != 0x1234 )
        return TEST_BROKEN;


    Universal_CRC<16, 0, 0x1234, true, false, 0>  ucrc1;


    if( ucrc1.get_crc_init() != 0x2c48 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



ptest_func tests[] =
{

    //CRC_Type_Helper
    test_crc_type_helper_uint8,
    test_crc_type_helper_uint16,
    test_crc_type_helper_uint32,
    test_crc_type_helper_uint64,


    //Universal_CRC methods
    test_universal_crc_name,
    test_universal_crc_name_2,

    test_universal_crc_get_bits,
    test_universal_crc_get_poly,
    test_universal_crc_get_init,
    test_universal_crc_get_xor_out,
    test_universal_crc_get_ref_in,
    test_universal_crc_get_ref_out,

    test_universal_crc_get_crc_init
};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}
