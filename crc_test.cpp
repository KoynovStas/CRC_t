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



//width=6 poly=0x27 init=0x3f refin=false refout=false xorout=0x00 check=0x0d name="CRC-6/CDMA2000-A"
int test_ucrc6(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<6, 0x27, 0x3f, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x0d )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=6 poly=0x07 init=0x3f refin=false refout=false xorout=0x00 check=0x3b name="CRC-6/CDMA2000-B"
int test_ucrc6_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<6, 0x07, 0x3f, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x3b )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=6 poly=0x19 init=0x00 refin=true refout=true xorout=0x00 check=0x26 name="CRC-6/DARC"
int test_ucrc6_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<6, 0x19, 0x0, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x26 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=6 poly=0x03 init=0x00 refin=true refout=true xorout=0x00 check=0x06 name="CRC-6/ITU"
int test_ucrc6_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<6, 0x03, 0x0, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x06 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=7 poly=0x09 init=0x00 refin=false refout=false xorout=0x00 check=0x75 name="CRC-7"
int test_ucrc7(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<7, 0x09, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x75 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=7 poly=0x4f init=0x7f refin=true refout=true xorout=0x00 check=0x53 name="CRC-7/ROHC"
int test_ucrc7_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<7, 0x4f, 0x7f, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x53 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_ucrc8(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0x31, 0xFF, false, false, 0x00>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xF7 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x07 init=0x00 refin=false refout=false xorout=0x00 check=0xf4 name="CRC-8"
int test_ucrc8_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0x07, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xF4 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x9b init=0xff refin=false refout=false xorout=0x00 check=0xda name="CRC-8/CDMA2000"
int test_ucrc8_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0x9b, 0xff, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xDA )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x39 init=0x00 refin=true refout=true xorout=0x00 check=0x15 name="CRC-8/DARC"
int test_ucrc8_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0x39, 0x0, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x15 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0xd5 init=0x00 refin=false refout=false xorout=0x00 check=0xbc name="CRC-8/DVB-S2"
int test_ucrc8_5(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0xd5, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xBC )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x1d init=0xff refin=true refout=true xorout=0x00 check=0x97 name="CRC-8/EBU"
int test_ucrc8_6(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0x1d, 0xff, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x97 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x1d init=0xfd refin=false refout=false xorout=0x00 check=0x7e name="CRC-8/I-CODE"
int test_ucrc8_7(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0x1d, 0xfd, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x7E )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x07 init=0x00 refin=false refout=false xorout=0x55 check=0xa1 name="CRC-8/ITU"
int test_ucrc8_8(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0x07, 0x00, false, false, 0x55>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xA1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x31 init=0x00 refin=true refout=true xorout=0x00 check=0xa1 name="CRC-8/MAXIM"
int test_ucrc8_9(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0x31, 0x00, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xA1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x07 init=0xff refin=true refout=true xorout=0x00 check=0xd0 name="CRC-8/ROHC"
int test_ucrc8_10(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0x07, 0xff, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xD0 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=8 poly=0x9b init=0x00 refin=true refout=true xorout=0x00 check=0x25 name="CRC-8/WCDMA"
int test_ucrc8_11(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    Universal_CRC<8, 0x9b, 0x00, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x25 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=10 poly=0x233 init=0x000 refin=false refout=false xorout=0x000 check=0x199 name="CRC-10"
int test_ucrc10(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<10, 0x233, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x199 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=10 poly=0x3d9 init=0x3ff refin=false refout=false xorout=0x000 check=0x233 name="CRC-10/CDMA2000"
int test_ucrc10_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<10, 0x3d9, 0x3ff, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x233 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=11 poly=0x385 init=0x01a refin=false refout=false xorout=0x000 check=0x5a3 name="CRC-11"
int test_ucrc11(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<11, 0x385, 0x01a, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x5A3 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=12 poly=0x80f init=0x000 refin=false refout=true xorout=0x000 check=0xdaf name="CRC-12/3GPP"
int test_ucrc12(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<12, 0x80f, 0x0, false, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xDAF )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=12 poly=0xf13 init=0xfff refin=false refout=false xorout=0x000 check=0xd4d name="CRC-12/CDMA2000"
int test_ucrc12_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<12, 0xf13, 0xfff, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xD4D )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=12 poly=0x80f init=0x000 refin=false refout=false xorout=0x000 check=0xf5b name="CRC-12/DECT"
int test_ucrc12_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<12, 0x80f, 0x0, false, false, 0x0>  ucrc;


    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xF5B )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=13 poly=0x1cf5 init=0x0000 refin=false refout=false xorout=0x0000 check=0x04fa name="CRC-13/BBC"
int test_ucrc13(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<13, 0x1cf5, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x04FA )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=14 poly=0x0805 init=0x0000 refin=true refout=true xorout=0x0000 check=0x082d name="CRC-14/DARC"
int test_ucrc14(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<14, 0x0805, 0x0, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x082D )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=15 poly=0x4599 init=0x0000 refin=false refout=false xorout=0x0000 check=0x059e name="CRC-15"
int test_ucrc15(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<15, 0x4599, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x059E )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=15 poly=0x6815 init=0x0000 refin=false refout=false xorout=0x0001 check=0x2566 name="CRC-15/MPT1327"
int test_ucrc15_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<15, 0x6815, 0x0, false, false, 0x1>  ucrc;


    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x2566 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0x0000  refin=true  refout=true  xorout=0x0000  check=0xbb3d  name="CRC-16/ARC"
int test_ucrc16(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<16, 0x8005, 0x0, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xbb3d )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0x1d0f  refin=false  refout=false  xorout=0x0000  check=0xe5cc  name="CRC-16/AUG-CCITT"
int test_ucrc16_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<16, 0x1021, 0x1d0f, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xe5cc )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0x0000  refin=false  refout=false  xorout=0x0000  check=0xfee8  name="CRC-16/BUYPASS"
int test_ucrc16_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<16, 0x8005, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xfee8 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0xffff  refin=false  refout=false  xorout=0x0000  check=0x29b1  name="CRC-16/CCITT-FALSE"
int test_ucrc16_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<16, 0x1021, 0xffff, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x29b1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0xc867  init=0xffff  refin=false  refout=false  xorout=0x0000  check=0x4c06  name="CRC-16/CDMA2000"
int test_ucrc16_5(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<16, 0xc867, 0xffff, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x4c06 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0x800d  refin=false  refout=false  xorout=0x0000  check=0x9ecf  name="CRC-16/DDS-110"
int test_ucrc16_6(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    Universal_CRC<16, 0x8005, 0x800d, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x9ecf )
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
    test_ucrc5_3,

    test_ucrc6,
    test_ucrc6_2,
    test_ucrc6_3,
    test_ucrc6_4,

    test_ucrc7,
    test_ucrc7_2,

    test_ucrc8,
    test_ucrc8_2,
    test_ucrc8_3,
    test_ucrc8_4,
    test_ucrc8_5,
    test_ucrc8_6,
    test_ucrc8_7,
    test_ucrc8_8,
    test_ucrc8_9,
    test_ucrc8_10,
    test_ucrc8_11,

    test_ucrc10,
    test_ucrc10_2,

    test_ucrc11,

    test_ucrc12,
    test_ucrc12_2,
    test_ucrc12_3,

    test_ucrc13,

    test_ucrc14,

    test_ucrc15,
    test_ucrc15_2,

    test_ucrc16,
    test_ucrc16_2,
    test_ucrc16_3,
    test_ucrc16_4,
    test_ucrc16_5,
    test_ucrc16_6
};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}
