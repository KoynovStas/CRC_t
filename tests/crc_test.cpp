#include <cstdlib>
#include <cstring>
#define __STDC_FORMAT_MACROS //for MinGW
#include <cinttypes>
#include <unistd.h>

#include "crc_list.h"



const uint8_t std_check_data[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};



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
    for(size_t i = 0; i < CRC_List.size(); i++)
    {
        TEST_ASSERTF(CRC_List[i]->get_bits() == CRC_List[i]->bits,
                     "For CRC: %s bits must be: %d but get: %d",
                     CRC_List[i]->name,
                     (int)CRC_List[i]->bits,
                     (int)CRC_List[i]->get_bits());
    }

    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_poly)
{
    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        TEST_ASSERTF(CRC_List[i]->get_poly() == CRC_List[i]->poly,
                     "For CRC: %s poly must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     CRC_List[i]->name,
                     CRC_List[i]->poly,
                     CRC_List[i]->get_poly());
    }

    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_init)
{
    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        TEST_ASSERTF(CRC_List[i]->get_init() == CRC_List[i]->init,
                     "For CRC: %s init must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     CRC_List[i]->name,
                     CRC_List[i]->init,
                     CRC_List[i]->get_init());
    }

    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_xor_out)
{
    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        TEST_ASSERTF(CRC_List[i]->get_xor_out() == CRC_List[i]->xor_out,
                     "For CRC: %s Xor_out must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     CRC_List[i]->name,
                     CRC_List[i]->xor_out,
                     CRC_List[i]->get_xor_out());
    }

    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_ref_in)
{
    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        TEST_ASSERTF(CRC_List[i]->get_ref_in() == CRC_List[i]->ref_in,
                     "For CRC: %s ref_in must be: %d but get: %d",
                     CRC_List[i]->name,
                     CRC_List[i]->ref_in,
                     CRC_List[i]->get_ref_in());
    }

    TEST_PASS(NULL);
}



TEST(test_universal_crc_get_ref_out)
{
    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        TEST_ASSERTF(CRC_List[i]->get_ref_out() == CRC_List[i]->ref_out,
                     "For CRC: %s ref_out must be: %d but get: %d",
                     CRC_List[i]->name,
                     CRC_List[i]->ref_out,
                     CRC_List[i]->get_ref_out());
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


    CRC_t<28, 0, 0, true, false, 0>  ucrc28;
    TEST_ASSERT(ucrc28.get_top_bit() == 0x8000000);


    CRC_t<32, 0, 0, true, false, 0>  ucrc32;
    TEST_ASSERT(ucrc32.get_top_bit() == 0x80000000);


    CRC_t<40, 0, 0, true, false, 0>  ucrc40;
    TEST_ASSERT(ucrc40.get_top_bit() == 0x8000000000);


    CRC_t<64, 0, 0, true, false, 0>  ucrc64;
    TEST_ASSERT(ucrc64.get_top_bit() == 0x8000000000000000);


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


    CRC_t<32, 0, 0, true, false, 0>  ucrc32;
    TEST_ASSERT(ucrc32.get_crc_mask() == 0xffffffff );


    TEST_PASS(NULL);
}



//------------- tests for Calculate CRC  -------------



TEST(test_crc_std_check)
{
    uint64_t crc;

    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        crc = CRC_List[i]->get_crc(std_check_data, sizeof(std_check_data));

        TEST_ASSERTF(crc == CRC_List[i]->check,
                     "For CRC: %s std check must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     CRC_List[i]->name,
                     CRC_List[i]->check,
                     crc);

        TEST_ASSERTF(CRC_List[i]->get_check() == CRC_List[i]->check,
                     "For CRC: %s std check must be: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     CRC_List[i]->name,
                     CRC_List[i]->check,
                     CRC_List[i]->get_check());
    }

    TEST_PASS(NULL);
}




//------------- tests for Calculate CRC different IMPL -------------


TEST(test_crc_impl_1byte)
{
    uint64_t crc1, crc2;
    uint8_t test_byte;

    for(int i = 0; i < 256; i++)//test all bytes
    {
        test_byte = i;

        //test all impl
        for(size_t i = 0; i < CRC_List.size(); i += CNT_IMPL)
        {
            crc1 = CRC_List[i]->get_crc(&test_byte, sizeof(test_byte));

            for(size_t j = 1; j < CNT_IMPL; j++)
            {
                crc2 = CRC_List[i+j]->get_crc(&test_byte, sizeof(test_byte));
                TEST_ASSERTF(crc1 == crc2,
                             "For CRC: %s crc: 0x%" PRIX64 " but for: %s crc: 0x%" PRIX64,
                             CRC_List[i]->name,
                             crc1,
                             CRC_List[i+j]->name,
                             crc2);
            }
        }
    }

    TEST_PASS(NULL);
}



TEST(test_crc_impl_data_xyz_256)
{
    uint64_t crc1, crc2;
    uint8_t test_data[256];

    for(int i = 0; i < 256; i++)
        test_data[i] = i;


    for(size_t i = 0; i < CRC_List.size(); i += CNT_IMPL)
    {
        crc1 = CRC_List[i]->get_crc(test_data, sizeof(test_data));

        for(size_t j = 1; j < CNT_IMPL; j++)
        {
            crc2 = CRC_List[i+j]->get_crc(test_data, sizeof(test_data));
            TEST_ASSERTF(crc1 == crc2,
                         "For CRC: %s crc: 0x%" PRIX64 " but for: %s crc: 0x%" PRIX64,
                         CRC_List[i]->name,
                         crc1,
                         CRC_List[i+j]->name,
                         crc2);
        }
    }


    TEST_PASS(NULL);
}



TEST(test_crc_impl_data_xxx_256)
{
    uint64_t crc1, crc2;
    uint8_t test_data[256];

    for(int i = 0; i < 256; i++)
    {
        memset(test_data, i, sizeof(test_data));


        for(size_t i = 0; i < CRC_List.size(); i += CNT_IMPL)
        {
            crc1 = CRC_List[i]->get_crc(test_data, sizeof(test_data));

            for(size_t j = 1; j < CNT_IMPL; j++)
            {
                crc2 = CRC_List[i+j]->get_crc(test_data, sizeof(test_data));
                TEST_ASSERTF(crc1 == crc2,
                             "For CRC: %s crc: 0x%" PRIX64 " but for: %s crc: 0x%" PRIX64,
                             CRC_List[i]->name,
                             crc1,
                             CRC_List[i+j]->name,
                             crc2);
            }
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

        TEST_ASSERTF((res == 0) &&  (crc == CRC_List[i]->check),
                     "For CRC: %s std check: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     CRC_List[i]->name,
                     CRC_List[i]->check,
                     crc);
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

        TEST_ASSERTF((res == -1) && (crc == 0),
                     "For CRC: %s no file but get_crc() ret: %d crc: 0x%" PRIX64,
                     CRC_List[i]->name,
                     res,
                     crc);
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

        TEST_ASSERTF(crc == CRC_List[i]->check,
                     "For CRC: %s std check: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     CRC_List[i]->name,
                     CRC_List[i]->check,
                     crc);
    }

    TEST_PASS(NULL);
}



TEST(test_crc_for_cunks2) //use wrapper for first chunk of data
{
    uint64_t crc;

    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        crc = CRC_List[i]->get_raw_crc(&std_check_data[0], 4);
        crc = CRC_List[i]->get_raw_crc(&std_check_data[4], 5, crc);
        crc = CRC_List[i]->get_end_crc(crc);

        TEST_ASSERTF(crc == CRC_List[i]->check,
                     "For CRC: %s std check: 0x%" PRIX64 " but get: 0x%" PRIX64,
                     CRC_List[i]->name,
                     CRC_List[i]->check,
                     crc);
    }

    TEST_PASS(NULL);
}



stest_func tests[] =
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
    test_crc_impl_1byte,
    test_crc_impl_data_xyz_256,
    test_crc_impl_data_xxx_256,

    test_crc_std_check_file,
    test_crc_no_file,

    test_crc_for_cunks,
    test_crc_for_cunks2,
};


MAIN_TESTS(tests)
