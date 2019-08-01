#include <stdlib.h>
#include <unistd.h>

#include <vector>
#include <string>
#include <iostream>
#include <sstream>

#include "stest.h"



#include "crc_list.h"



const uint8_t std_check_data[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};



static std::stringstream ss;
static std::string       msg;


void test_init(struct test_case_t *test_case)
{
    ss.clear();
    ss.str(""); // clear ss
    ss << std::hex;

    msg.clear();
}




//------------- tests for CRC_Type_helper -------------



TEST(test_crc_type_helper_uint8)
{

    TEST_ASSERT(sizeof(CRC_Type_helper< (1-1)/8 >::value_type) == sizeof(uint8_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (2-1)/8 >::value_type) == sizeof(uint8_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (3-1)/8 >::value_type) == sizeof(uint8_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (4-1)/8 >::value_type) == sizeof(uint8_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (5-1)/8 >::value_type) == sizeof(uint8_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (6-1)/8 >::value_type) == sizeof(uint8_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (7-1)/8 >::value_type) == sizeof(uint8_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (8-1)/8 >::value_type) == sizeof(uint8_t));

    TEST_PASS(NULL);
}



TEST(test_crc_type_helper_uint16)
{

    TEST_ASSERT(sizeof(CRC_Type_helper< (9 -1)/8 >::value_type) == sizeof(uint16_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (10-1)/8 >::value_type) == sizeof(uint16_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (11-1)/8 >::value_type) == sizeof(uint16_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (12-1)/8 >::value_type) == sizeof(uint16_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (13-1)/8 >::value_type) == sizeof(uint16_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (14-1)/8 >::value_type) == sizeof(uint16_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (15-1)/8 >::value_type) == sizeof(uint16_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (16-1)/8 >::value_type) == sizeof(uint16_t));

    TEST_PASS(NULL);
}



TEST(test_crc_type_helper_uint32)
{

    TEST_ASSERT(sizeof(CRC_Type_helper< (17-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (18-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (19-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (20-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (21-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (22-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (23-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (24-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (25-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (26-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (27-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (28-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (29-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (30-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (31-1)/8 >::value_type) == sizeof(uint32_t));
    TEST_ASSERT(sizeof(CRC_Type_helper< (32-1)/8 >::value_type) == sizeof(uint32_t));

    TEST_PASS(NULL);
}



TEST(test_crc_type_helper_uint64)
{
    //Template CRC_Type_helper default is uint64_t
    TEST_ASSERT(sizeof(CRC_Type_helper<100>::value_type) == sizeof(uint64_t));

    TEST_PASS(NULL);
}



//------------- tests for Universal_CRC methods -------------



TEST(test_universal_crc_get_bits)
{

    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_bits() != CRC_List[i]->bits )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  " bits must be: " << CRC_List[i]->bits << " but get: " << CRC_List[i]->get_bits();
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }
    }


    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_poly)
{

    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_poly() != CRC_List[i]->poly )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  " poly must be: " << CRC_List[i]->poly << " but get: " << CRC_List[i]->get_poly();
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }
    }


    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_init)
{

    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_init() != CRC_List[i]->init )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  " Init must be: " << CRC_List[i]->init << " but get: " << CRC_List[i]->get_init();
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }
    }


    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_xor_out)
{

    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_xor_out() != CRC_List[i]->xor_out )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  " Xor_out must be: " << CRC_List[i]->xor_out << " but get: " << CRC_List[i]->get_xor_out();
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }
    }


    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_ref_in)
{

    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_ref_in() != CRC_List[i]->ref_in )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  " ref_in must be: " << CRC_List[i]->ref_in << " but get: " << CRC_List[i]->get_ref_in();
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }
    }


    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_ref_out)
{

    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_ref_out() != CRC_List[i]->ref_out )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  " ref_out must be: " << CRC_List[i]->ref_out << " but get: " << CRC_List[i]->get_ref_out();
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }
    }


    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_crc_init)
{
    CRC_t<16, 0, 0x1234, false, false, 0>  ucrc;
    TEST_ASSERT(ucrc.get_crc_init() == 0x1234);


    CRC_t<16, 0, 0x1234, true, false, 0>  ucrc1;
    TEST_ASSERT(ucrc1.get_crc_init() == 0x2c48 );


    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_top_bit)
{
    CRC_t<1, 0, 0, true, false, 0>  ucrc1;
    TEST_ASSERT(ucrc1.get_top_bit() == 0x1);


    CRC_t<5, 0, 0, true, false, 0>  ucrc5;
    TEST_ASSERT(ucrc5.get_top_bit() == 0x10);


    CRC_t<8, 0, 0, true, false, 0>  ucrc8;
    TEST_ASSERT(ucrc8.get_top_bit() == 0x80);


    CRC_t<16, 0, 0, true, false, 0>  ucrc16;
    TEST_ASSERT(ucrc16.get_top_bit() == 0x8000);


    CRC_t<24, 0, 0, true, false, 0>  ucrc24;
    TEST_ASSERT(ucrc24.get_top_bit() == 0x800000);


    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_crc_mask)
{
    CRC_t<1, 0, 0, true, false, 0>  ucrc1;
    TEST_ASSERT(ucrc1.get_crc_mask() == 0x0001 );


    CRC_t<5, 0, 0, true, false, 0>  ucrc5;
    TEST_ASSERT(ucrc5.get_crc_mask() == 0x1f );


    CRC_t<8, 0, 0, true, false, 0>  ucrc8;
    TEST_ASSERT(ucrc8.get_crc_mask() == 0xff );


    CRC_t<16, 0, 0, true, false, 0>  ucrc16;
    TEST_ASSERT(ucrc16.get_crc_mask() == 0xffff );


    CRC_t<24, 0, 0, true, false, 0>  ucrc24;
    TEST_ASSERT(ucrc24.get_crc_mask() == 0xffffff );


    TEST_PASS(NULL);
}



//------------- tests for Calculate CRC  -------------



TEST(test_crc_std_check)
{
    uint64_t crc;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        crc = CRC_List[i]->get_crc(std_check_data, sizeof(std_check_data));

        if( crc != CRC_List[i]->check )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  " std check: 0x" << CRC_List[i]->check << " but get: 0x" << crc;
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }


        if( CRC_List[i]->get_check() != CRC_List[i]->check )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  " std check: 0x" << CRC_List[i]->check << " but get_check: 0x" << CRC_List[i]->get_check();
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }
    }


    TEST_PASS(NULL);
}



//------------- tests for Calculate CRC for file -------------



TEST(test_crc_std_check_file)
{
    uint64_t crc;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        crc = 0;
        int res = CRC_List[i]->get_crc(crc, "std_file_to_test_crc");

        if( (res != 0) ||  (crc != CRC_List[i]->check) )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  " std check: 0x" << CRC_List[i]->check << " but get: 0x" << crc;
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }
    }


    TEST_PASS(NULL);
}



TEST(test_crc_no_file)
{
    uint64_t crc;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        crc = 0;
        int res = CRC_List[i]->get_crc(crc, "");

        if( (res != -1) || (crc != 0) )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  "no file but get_crc() ret:" << res << " crc:" << crc;
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }
    }


    TEST_PASS(NULL);
}



//------------- tests for Calculate CRC for cunks -------------



TEST(test_crc_for_cunks)
{
    uint64_t crc;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        crc = CRC_List[i]->get_crc_init();
        crc = CRC_List[i]->get_raw_crc(&std_check_data[0], 4, crc);
        crc = CRC_List[i]->get_raw_crc(&std_check_data[4], 5, crc);
        crc = CRC_List[i]->get_end_crc(crc);

        if( crc != CRC_List[i]->check )
        {
            ss << "For CRC: " << CRC_List[i]->name <<  " std check: 0x" << CRC_List[i]->check << " but get: 0x" << crc;
            msg = ss.str();
            TEST_FAIL(msg.c_str());
        }
    }


    TEST_PASS(NULL);
}



ptest_func tests[] =
{

    //CRC_Type_Helper
    test_crc_type_helper_uint8,
    test_crc_type_helper_uint16,
    test_crc_type_helper_uint32,
    test_crc_type_helper_uint64,


    //Universal_CRC methods
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
    test_crc_std_check,

    test_crc_std_check_file,
    test_crc_no_file,

    test_crc_for_cunks,
};


TEST_CASE(test_case, tests, NULL, test_init, NULL)


MAIN_CASE(test_case)
