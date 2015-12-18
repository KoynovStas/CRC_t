#include "unit_tests.h"
#include "crc_t.h"




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


    CRC_t<1, 0, 0, true, true, 0>  ucrc;


    if( ucrc.name != "" )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_name_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    const char* name = "some_name";

    CRC_t<1, 0, 0, true, true, 0>  ucrc(name);


    if( ucrc.name != name )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_bits(struct test_info_t  *test_info)
{

    TEST_INIT;

    CRC_t<1, 0, 0, true, true, 0>  ucrc_1;


    if( ucrc_1.get_bits() != 1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_poly(struct test_info_t  *test_info)
{

    TEST_INIT;

    CRC_t<16, 1234, 0, true, true, 0>  ucrc;


    if( ucrc.get_poly() != 1234 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_init(struct test_info_t  *test_info)
{

    TEST_INIT;

    CRC_t<16, 0, 1234, true, true, 0>  ucrc;


    if( ucrc.get_init() != 1234 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_xor_out(struct test_info_t  *test_info)
{

    TEST_INIT;

    CRC_t<16, 0, 0, true, false, 4321>  ucrc;


    if( ucrc.get_xor_out() != 4321 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_ref_in(struct test_info_t  *test_info)
{

    TEST_INIT;

    CRC_t<16, 0, 0, true, false, 4321>  ucrc;


    if( ucrc.get_ref_in() != true )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_ref_out(struct test_info_t  *test_info)
{

    TEST_INIT;

    CRC_t<16, 0, 0, true, false, 4321>  ucrc;


    if( ucrc.get_ref_out() != false )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_crc_init(struct test_info_t  *test_info)
{

    TEST_INIT;

    CRC_t<16, 0, 0x1234, false, false, 0>  ucrc;


    if( ucrc.get_crc_init() != 0x1234 )
        return TEST_BROKEN;


    CRC_t<16, 0, 0x1234, true, false, 0>  ucrc1;


    if( ucrc1.get_crc_init() != 0x2c48 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_top_bit(struct test_info_t  *test_info)
{

    TEST_INIT;

    CRC_t<1, 0, 0, true, false, 0>  ucrc1;
    if( ucrc1.get_top_bit() != 0x1 )
        return TEST_BROKEN;


    CRC_t<5, 0, 0, true, false, 0>  ucrc5;
    if( ucrc5.get_top_bit() != 0x10 )
        return TEST_BROKEN;


    CRC_t<8, 0, 0, true, false, 0>  ucrc8;
    if( ucrc8.get_top_bit() != 0x80 )
        return TEST_BROKEN;


    CRC_t<16, 0, 0, true, false, 0>  ucrc16;
    if( ucrc16.get_top_bit() != 0x8000 )
        return TEST_BROKEN;


    CRC_t<24, 0, 0, true, false, 0>  ucrc24;
    if( ucrc24.get_top_bit() != 0x800000 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_universal_crc_get_crc_mask(struct test_info_t  *test_info)
{

    TEST_INIT;

    CRC_t<1, 0, 0, true, false, 0>  ucrc1;
    if( ucrc1.get_crc_mask() != 0x0001 )
        return TEST_BROKEN;


    CRC_t<5, 0, 0, true, false, 0>  ucrc5;
    if( ucrc5.get_crc_mask() != 0x1f )
        return TEST_BROKEN;


    CRC_t<8, 0, 0, true, false, 0>  ucrc8;
    if( ucrc8.get_crc_mask() != 0xff )
        return TEST_BROKEN;


    CRC_t<16, 0, 0, true, false, 0>  ucrc16;
    if( ucrc16.get_crc_mask() != 0xffff )
        return TEST_BROKEN;


    CRC_t<24, 0, 0, true, false, 0>  ucrc24;
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

    CRC_t<3, 0x3, 0x7, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x6 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_ucrc4(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t<4, 0x3, 0x0, false, false, 0x0>  ucrc;

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

    CRC_t<4, 0x3, 0x0, true, true, 0x0>  ucrc;

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

    CRC_t<5, 0x09, 0x09, false, false, 0x0>  ucrc;

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

    CRC_t<5, 0x15, 0x00, true, true, 0x0>  ucrc;

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

    CRC_t<5, 0x05, 0x1f, true, true, 0x1f>  ucrc;

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

    CRC_t<6, 0x27, 0x3f, false, false, 0x0>  ucrc;

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

    CRC_t<6, 0x07, 0x3f, false, false, 0x0>  ucrc;

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

    CRC_t<6, 0x19, 0x0, true, true, 0x0>  ucrc;

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

    CRC_t<6, 0x03, 0x0, true, true, 0x0>  ucrc;

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

    CRC_t<7, 0x09, 0x0, false, false, 0x0>  ucrc;

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

    CRC_t<7, 0x4f, 0x7f, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x53 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_ucrc8(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint8_t crc;

    CRC_t<8, 0x31, 0xFF, false, false, 0x00>  ucrc;

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

    CRC_t<8, 0x07, 0x0, false, false, 0x0>  ucrc;

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

    CRC_t<8, 0x9b, 0xff, false, false, 0x0>  ucrc;

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

    CRC_t<8, 0x39, 0x0, true, true, 0x0>  ucrc;

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

    CRC_t<8, 0xd5, 0x0, false, false, 0x0>  ucrc;

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

    CRC_t<8, 0x1d, 0xff, true, true, 0x0>  ucrc;

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

    CRC_t<8, 0x1d, 0xfd, false, false, 0x0>  ucrc;

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

    CRC_t<8, 0x07, 0x00, false, false, 0x55>  ucrc;

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

    CRC_t<8, 0x31, 0x00, true, true, 0x0>  ucrc;

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

    CRC_t<8, 0x07, 0xff, true, true, 0x0>  ucrc;

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

    CRC_t<8, 0x9b, 0x00, true, true, 0x0>  ucrc;

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

    CRC_t<10, 0x233, 0x0, false, false, 0x0>  ucrc;

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

    CRC_t<10, 0x3d9, 0x3ff, false, false, 0x0>  ucrc;

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

    CRC_t<11, 0x385, 0x01a, false, false, 0x0>  ucrc;

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

    CRC_t<12, 0x80f, 0x0, false, true, 0x0>  ucrc;

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

    CRC_t<12, 0xf13, 0xfff, false, false, 0x0>  ucrc;

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

    CRC_t<12, 0x80f, 0x0, false, false, 0x0>  ucrc;


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

    CRC_t<13, 0x1cf5, 0x0, false, false, 0x0>  ucrc;

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

    CRC_t<14, 0x0805, 0x0, true, true, 0x0>  ucrc;

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

    CRC_t<15, 0x4599, 0x0, false, false, 0x0>  ucrc;

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

    CRC_t<15, 0x6815, 0x0, false, false, 0x1>  ucrc;


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

    CRC_t<16, 0x8005, 0x0, true, true, 0x0>  ucrc;

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

    CRC_t<16, 0x1021, 0x1d0f, false, false, 0x0>  ucrc;

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

    CRC_t<16, 0x8005, 0x0, false, false, 0x0>  ucrc;

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

    CRC_t<16, 0x1021, 0xffff, false, false, 0x0>  ucrc;

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

    CRC_t<16, 0xc867, 0xffff, false, false, 0x0>  ucrc;

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

    CRC_t<16, 0x8005, 0x800d, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x9ecf )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x0589  init=0x0000  refin=false  refout=false  xorout=0x0001  check=0x007e  name="CRC-16/DECT-R"
int test_ucrc16_7(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x0589, 0x0, false, false, 0x0001>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x007e )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x0589  init=0x0000  refin=false  refout=false  xorout=0x0000  check=0x007f  name="CRC-16/DECT-X"
int test_ucrc16_8(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x0589, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x007f )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x3d65  init=0x0000  refin=true  refout=true  xorout=0xffff  check=0xea82  name="CRC-16/DNP"
int test_ucrc16_9(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x3d65, 0x0, true, true, 0xffff>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xea82 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x3d65  init=0x0000  refin=false  refout=false  xorout=0xffff  check=0xc2b7  name="CRC-16/EN-13757"
int test_ucrc16_10(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x3d65, 0x0, false, false, 0xffff>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xc2b7 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0xffff  refin=false  refout=false  xorout=0xffff  check=0xd64e  name="CRC-16/GENIBUS"
int test_ucrc16_11(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x1021, 0xffff, false, false, 0xffff>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xd64e )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0x0000  refin=true  refout=true  xorout=0xffff  check=0x44c2  name="CRC-16/MAXIM"
int test_ucrc16_12(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x8005, 0x0, true, true, 0xffff>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x44c2 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0xffff  refin=true  refout=true  xorout=0x0000  check=0x6f91  name="CRC-16/MCRF4XX"
int test_ucrc16_13(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x1021, 0xffff, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x6f91 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0xb2aa  refin=true  refout=true  xorout=0x0000  check=0x63d0  name="CRC-16/RIELLO"
int test_ucrc16_14(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x1021, 0xb2aa, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x63d0 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8bb7  init=0x0000  refin=false  refout=false  xorout=0x0000  check=0xd0db  name="CRC-16/T10-DIF"
int test_ucrc16_15(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x8bb7, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xd0db )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0xa097  init=0x0000  refin=false  refout=false  xorout=0x0000  check=0x0fb3  name="CRC-16/TELEDISK"
int test_ucrc16_16(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0xa097, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x0fb3 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0x89ec  refin=true  refout=true  xorout=0x0000  check=0x26b1  name="CRC-16/TMS37157"
int test_ucrc16_17(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x1021, 0x89ec, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x26b1 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0xffff  refin=true  refout=true  xorout=0xffff  check=0xb4c8  name="CRC-16/USB"
int test_ucrc16_18(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x8005, 0xffff, true, true, 0xffff>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xb4c8 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0xc6c6  refin=true  refout=true  xorout=0x0000  check=0xbf05  name="CRC-A"
int test_ucrc16_19(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x1021, 0xc6c6, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xbf05 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0x0000  refin=true  refout=true  xorout=0x0000  check=0x2189  name="CRC-16/KERMIT"
int test_ucrc16_20(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x1021, 0x0, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x2189 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x8005  init=0xffff  refin=true  refout=true  xorout=0x0000  check=0x4b37  name="CRC-16/MODBUS"
int test_ucrc16_21(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x8005, 0xffff, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x4b37 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0xffff  refin=true  refout=true  xorout=0xffff  check=0x906e  name="CRC-16/X-25"
int test_ucrc16_22(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x1021, 0xffff, true, true, 0xffff>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x906e )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=16  poly=0x1021  init=0x0000  refin=false  refout=false  xorout=0x0000  check=0x31c3  name="XMODEM"
int test_ucrc16_23(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint16_t crc;

    CRC_t<16, 0x1021, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x31c3 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=24 poly=0x864cfb init=0xb704ce refin=false refout=false xorout=0x000000 check=0x21cf02 name="CRC-24"
int test_ucrc24(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<24, 0x864cfb, 0xb704ce, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x21cf02 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=24 poly=0x5d6dcb init=0xfedcba refin=false refout=false xorout=0x000000 check=0x7979bd name="CRC-24/FLEXRAY-A"
int test_ucrc24_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<24, 0x5d6dcb, 0xfedcba, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x7979bd )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=24 poly=0x5d6dcb init=0xabcdef refin=false refout=false xorout=0x000000 check=0x1f23b8 name="CRC-24/FLEXRAY-B"
int test_ucrc24_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<24, 0x5d6dcb, 0xabcdef, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x1f23b8 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=31 poly=0x04c11db7 init=0x7fffffff refin=false refout=false xorout=0x7fffffff check=0x0ce9e46c name="CRC-31/PHILIPS"
int test_ucrc31(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<31, 0x04c11db7, 0x7fffffff, false, false, 0x7fffffff>  ucrc;


    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x0ce9e46c )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=32 poly=0x04c11db7 init=0xffffffff refin=true refout=true xorout=0xffffffff check=0xcbf43926 name="CRC-32"
int test_ucrc32(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xCBF43926 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=32 poly=0x04c11db7 init=0xffffffff refin=false refout=false xorout=0xffffffff check=0xfc891918 name="CRC-32/BZIP2"
int test_ucrc32_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0x04c11db7, 0xFFFFFFFF, false, false, 0xFFFFFFFF>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xfc891918 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=32 poly=0x1edc6f41 init=0xffffffff refin=true refout=true xorout=0xffffffff check=0xe3069283 name="CRC-32C"
int test_ucrc32_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0x1edc6f41, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xe3069283 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=32 poly=0xa833982b init=0xffffffff refin=true refout=true xorout=0xffffffff check=0x87315576 name="CRC-32D"
int test_ucrc32_4(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0xa833982b, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x87315576 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=32 poly=0x04c11db7 init=0xffffffff refin=false refout=false xorout=0x00000000 check=0x0376e6e7 name="CRC-32/MPEG-2"
int test_ucrc32_5(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0x04c11db7, 0xFFFFFFFF, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x0376e6e7 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=32 poly=0x04c11db7 init=0x00000000 refin=false refout=false xorout=0xffffffff check=0x765e7680 name="CRC-32/POSIX"
int test_ucrc32_6(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0x04c11db7, 0x0, false, false, 0xffffffff>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x765e7680 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=32 poly=0x814141ab init=0x00000000 refin=false refout=false xorout=0x00000000 check=0x3010bf7f name="CRC-32Q"
int test_ucrc32_7(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0x814141ab, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x3010bf7f )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=32 poly=0x04c11db7 init=0xffffffff refin=true refout=true xorout=0x00000000 check=0x340bc6d9 name="JAMCRC"
int test_ucrc32_8(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0x04c11db7, 0xffffffff, true, true, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x340bc6d9 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=32 poly=0x000000af init=0x00000000 refin=false refout=false xorout=0x00000000 check=0xbd0be338 name="CRC-32/XFER"
int test_ucrc32_9(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0x000000af, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xbd0be338 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=40 poly=0x0004820009 init=0x0 refin=false refout=false xorout=0xffffffffff check=0xd4164fc646 name="CRC-40/GSM"
int test_ucrc40(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;

    CRC_t<40, 0x0004820009, 0x0, false, false, 0xffffffffff>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0xd4164fc646 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=64 poly=0x42f0e1eba9ea3693 init=0x0 refin=false refout=false xorout=0x0 check=0x6c40df5f0b497347 name="CRC-64"
int test_ucrc64(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;

    CRC_t<64, 0x42f0e1eba9ea3693, 0x0, false, false, 0x0>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x6c40df5f0b497347 )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=64 poly=0x42f0e1eba9ea3693 init=0xffffffffffffffff refin=false refout=false
//xorout=0xffffffffffffffff check=0x62ec59e3f1a4f00a name="CRC-64/WE"
int test_ucrc64_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;

    CRC_t<64, 0x42f0e1eba9ea3693, 0xffffffffffffffff, false, false, 0xffffffffffffffff>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x62ec59e3f1a4f00a )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//width=64 poly=0x42f0e1eba9ea3693 init=0xffffffffffffffff refin=true refout=true
//xorout=0xffffffffffffffff check=0x995dc9bbdf1939fa name="CRC-64/XZ"
int test_ucrc64_3(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;

    CRC_t<64, 0x42f0e1eba9ea3693, 0xFFFFFFFFFFFFFFFF, true, true, 0xFFFFFFFFFFFFFFFF>  ucrc;

    crc = ucrc.get_crc("123456789", 9);
    if( crc != 0x995dc9bbdf1939fa )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//------------- tests for Calculate CRC for file -------------



int test_ucrc32_file(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

    int res = ucrc.get_crc(&crc, "standard_check_file");

    if( (res != 0) ||  (crc != 0xCBF43926) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



int test_ucrc32_file_2(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    CRC_t<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

    int res = ucrc.get_crc(&crc, ""); //no file

    if( (res != -1) )
        return TEST_BROKEN;


    return TEST_PASSED;
}



//------------- tests for Calculate CRC for cunks -------------



int test_ucrc32_cunks(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint32_t crc;

    char buf[]  = "1234";
    char buf2[] = "56789";

    CRC_t<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

    crc = ucrc.get_crc_init();
    crc = ucrc.get_raw_crc(buf, 4, crc);
    crc = ucrc.get_raw_crc(buf2, 5, crc);
    crc = ucrc.get_final_crc(crc);


    if( crc != 0xCBF43926 )
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
    test_ucrc16_6,
    test_ucrc16_7,
    test_ucrc16_8,
    test_ucrc16_9,
    test_ucrc16_10,
    test_ucrc16_11,
    test_ucrc16_12,
    test_ucrc16_13,
    test_ucrc16_14,
    test_ucrc16_15,
    test_ucrc16_16,
    test_ucrc16_17,
    test_ucrc16_18,
    test_ucrc16_19,
    test_ucrc16_20,
    test_ucrc16_21,
    test_ucrc16_22,
    test_ucrc16_23,

    test_ucrc24,
    test_ucrc24_2,
    test_ucrc24_3,

    test_ucrc31,

    test_ucrc32,
    test_ucrc32_2,
    test_ucrc32_3,
    test_ucrc32_4,
    test_ucrc32_5,
    test_ucrc32_6,
    test_ucrc32_7,
    test_ucrc32_8,
    test_ucrc32_9,

    test_ucrc40,

    test_ucrc64,
    test_ucrc64_2,
    test_ucrc64_3,

    test_ucrc32_file,
    test_ucrc32_file_2,

    test_ucrc32_cunks
};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}
