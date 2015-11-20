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



int test_universal_crc_get_top_bit(struct test_info_t  *test_info)
{

    TEST_INIT;

    Universal_CRC<1, 0, 0, true, false, 0>  ucrc1;
    if( ucrc1.get_top_bit() != 0x1 )
        return TEST_BROKEN;


    Universal_CRC<5, 0, 0, true, false, 0>  ucrc5;
    if( ucrc5.get_top_bit() != 0x10 )
        return TEST_BROKEN;


    Universal_CRC<8, 0, 0, true, false, 0>  ucrc8;
    if( ucrc8.get_top_bit() != 0x80 )
        return TEST_BROKEN;


    Universal_CRC<16, 0, 0, true, false, 0>  ucrc16;
    if( ucrc16.get_top_bit() != 0x8000 )
        return TEST_BROKEN;


    Universal_CRC<24, 0, 0, true, false, 0>  ucrc24;
    if( ucrc24.get_top_bit() != 0x800000 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_crc_mask(struct test_info_t  *test_info)
{

    TEST_INIT;

    Universal_CRC<1, 0, 0, true, false, 0>  ucrc1;
    if( ucrc1.get_crc_mask() != 0x0001 )
        return TEST_BROKEN;


    Universal_CRC<5, 0, 0, true, false, 0>  ucrc5;
    if( ucrc5.get_crc_mask() != 0x1f )
        return TEST_BROKEN;


    Universal_CRC<8, 0, 0, true, false, 0>  ucrc8;
    if( ucrc8.get_crc_mask() != 0xff )
        return TEST_BROKEN;


    Universal_CRC<16, 0, 0, true, false, 0>  ucrc16;
    if( ucrc16.get_crc_mask() != 0xffff )
        return TEST_BROKEN;


    Universal_CRC<24, 0, 0, true, false, 0>  ucrc24;
    if( ucrc24.get_crc_mask() != 0xffffff )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//------------- tests for Calculate CRC  -------------



//width=3 poly=0x3 init=0x7 refin=true refout=true xorout=0x0 check=0x6 name="CRC-3/ROHC"
int test_ucrc3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<3, 0x3, 0x7, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x6 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_ucrc4(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<4, 0x3, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xE )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=4 poly=0x3 init=0x0 refin=true refout=true xorout=0x0 check=0x7 name="CRC-4/ITU"
int test_ucrc4_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<4, 0x3, 0x0, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x7 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=5 poly=0x09 init=0x09 refin=false refout=false xorout=0x00 check=0x00 name="CRC-5/EPC"
int test_ucrc5(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<5, 0x09, 0x09, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x0 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=5 poly=0x15 init=0x00 refin=true refout=true xorout=0x00 check=0x07 name="CRC-5/ITU"
int test_ucrc5_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<5, 0x15, 0x00, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x07 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=5 poly=0x05 init=0x1f refin=true refout=true xorout=0x1f check=0x19 name="CRC-5/USB"
int test_ucrc5_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<5, 0x05, 0x1f, true, true, 0x1f>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x19 )
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

    test_universal_crc_get_crc_init,
    test_universal_crc_get_top_bit,
    test_universal_crc_get_crc_mask,


    //CRC
    test_ucrc3,

    test_ucrc4,
    test_ucrc4_2,

    test_ucrc5,
    test_ucrc5_2,
    test_ucrc5_3
};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}
