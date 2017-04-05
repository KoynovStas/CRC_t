#include <stdlib.h>
#include <unistd.h>

#include <vector>
#include <string>
#include <iostream>

#include "unit_tests.h"
#include "crc_t.h"





class AbstractProxy_CRC_t
{

    public:

        virtual ~AbstractProxy_CRC_t(){}


        //specification
        std::string  name;
        uint8_t      bits;
        uint64_t     poly;
        uint64_t     init;
        bool         ref_in;
        bool         ref_out;
        uint64_t     xor_out;
        uint64_t     check;


        // get param CRC
        virtual uint8_t  get_bits()     = 0;
        virtual uint64_t get_poly()     = 0;
        virtual uint64_t get_init()     = 0;
        virtual uint64_t get_xor_out()  = 0;
        virtual bool     get_ref_in()   = 0;
        virtual bool     get_ref_out()  = 0;

        virtual uint64_t get_crc_init() = 0;
        virtual uint64_t get_top_bit()  = 0;
        virtual uint64_t get_crc_mask() = 0;

        // Calculate methods
        virtual uint64_t get_crc(const void* data, size_t len) = 0;
        virtual int      get_crc(uint64_t &crc, const char *file_name) = 0;
        virtual int      get_crc(uint64_t &crc, FILE* pfile) = 0;
        virtual int      get_crc(uint64_t &crc, const char* file_name, void* buf, size_t size_buf) = 0;
        virtual int      get_crc(uint64_t &crc, FILE* pfile, void* buf, size_t size_buf) = 0;


        // Calculate for chunks of data
        virtual uint64_t get_raw_crc(const void* data, size_t len, uint64_t crc) = 0;
        virtual uint64_t get_final_crc(uint64_t raw_crc) = 0;
};





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, uint64_t Check>
class Proxy_CRC_t : public AbstractProxy_CRC_t
{

    public:

        virtual ~Proxy_CRC_t(){}

        // get param CRC
        virtual uint8_t  get_bits()    { return _crc.get_bits();    }
        virtual uint64_t get_poly()    { return _crc.get_poly();    }
        virtual uint64_t get_init()    { return _crc.get_init();    }
        virtual uint64_t get_xor_out() { return _crc.get_xor_out(); }
        virtual bool     get_ref_in()  { return _crc.get_ref_in();  }
        virtual bool     get_ref_out() { return _crc.get_ref_out(); }

        virtual uint64_t get_crc_init() { return _crc.get_crc_init();}
        virtual uint64_t get_top_bit()  { return _crc.get_top_bit(); }
        virtual uint64_t get_crc_mask() { return _crc.get_crc_mask();}


        // Calculate methods
        virtual uint64_t get_crc(const void* data, size_t len)
                                { return _crc.get_crc(data, len); }

        virtual int      get_crc(uint64_t &crc, const char *file_name)
                                { return _crc.get_crc((CRC_TYPE &)crc, file_name); }

        virtual int      get_crc(uint64_t &crc, FILE* pfile)
                                { return _crc.get_crc((CRC_TYPE &)crc, pfile); }

        virtual int      get_crc(uint64_t &crc, const char* file_name, void* buf, size_t size_buf)
                                { return _crc.get_crc((CRC_TYPE &)crc, file_name, buf, size_buf); }

        virtual int      get_crc(uint64_t &crc, FILE* pfile, void* buf, size_t size_buf)
                                { return _crc.get_crc((CRC_TYPE &)crc, pfile, buf, size_buf); }


        //Calculate for chunks of data
        virtual uint64_t get_raw_crc(const void* data, size_t len, uint64_t crc)
                                    { return _crc.get_raw_crc(data, len, (CRC_TYPE)crc); }

        virtual uint64_t get_final_crc(uint64_t raw_crc)
                                      { return _crc.get_final_crc((CRC_TYPE)raw_crc); }

    private:

        CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>  _crc;
};





#define ADD_CRC_TO_LIST(Name, Bits, Poly, Init, RefIn, RefOut, XorOut, Check)                                            \
{                                                                                                                        \
    AbstractProxy_CRC_t *ptr = (AbstractProxy_CRC_t *)new Proxy_CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Check>(); \
    if( !ptr )                                                                                                           \
    {                                                                                                                    \
        std::cerr << "Can't get MEM for Proxy_CRC_t<" << Bits << "," << Poly << "," << Init << "," << RefIn << ","       \
                                                      << RefOut << "," << XorOut << "," << Check << ">";                 \
        exit(-1);                                                                                                        \
    }                                                                                                                    \
    ptr->name    = Name;                                                                                                 \
    ptr->bits    = Bits;                                                                                                 \
    ptr->poly    = Poly;                                                                                                 \
    ptr->init    = Init;                                                                                                 \
    ptr->ref_in  = RefIn;                                                                                                \
    ptr->ref_out = RefOut;                                                                                               \
    ptr->xor_out = XorOut;                                                                                               \
    ptr->check   = Check;                                                                                                \
                                                                                                                         \
    CRC_List.push_back(ptr);                                                                                             \
}                                                                                                                        \



std::vector<AbstractProxy_CRC_t *> get_crc_list()
{
    std::vector<AbstractProxy_CRC_t *> CRC_List;


    // CRC list from: http://reveng.sourceforge.net/crc-catalogue/all.htm

    // CRC-3
    ADD_CRC_TO_LIST("CRC-3/GSM",  3, 0x3, 0,   false, false, 0x7, 0x4);
    ADD_CRC_TO_LIST("CRC-3/ROHC", 3, 0x3, 0x7, true,  true,  0x0, 0x6);

    // CRC-4
    ADD_CRC_TO_LIST("CRC-4/ITU",        4, 0x3, 0x0, true,  true,  0x0, 0x7);
    ADD_CRC_TO_LIST("CRC-4/INTERLAKEN", 4, 0x3, 0xF, false, false, 0xF, 0xB);

    // CRC-5
    ADD_CRC_TO_LIST("CRC-5/EPC", 5, 0x09, 0x09, false, false, 0x00, 0x00);
    ADD_CRC_TO_LIST("CRC-5/ITU", 5, 0x15, 0x00, true,  true,  0x00, 0x07);
    ADD_CRC_TO_LIST("CRC-5/USB", 5, 0x05, 0x1F, true,  true,  0x1F, 0x19);

    // CRC-6
    ADD_CRC_TO_LIST("CRC-6/CDMA2000-A", 6, 0x27, 0x3F, false, false, 0x0,  0x0D);
    ADD_CRC_TO_LIST("CRC-6/CDMA2000-B", 6, 0x07, 0x3F, false, false, 0x0,  0x3B);
    ADD_CRC_TO_LIST("CRC-6/DARC",       6, 0x19, 0x00, true,  true,  0x0,  0x26);
    ADD_CRC_TO_LIST("CRC-6/ITU",        6, 0x03, 0x00, true,  true,  0x0,  0x06);
    ADD_CRC_TO_LIST("CRC-6/GSM",        6, 0x2F, 0x00, false, false, 0x3F, 0x13);

    // CRC-7
    ADD_CRC_TO_LIST("CRC-7",      7, 0x9,  0x0,  false, false, 0x0, 0x75);
    ADD_CRC_TO_LIST("CRC-7/ROHC", 7, 0x4F, 0x7F, true,  true,  0x0, 0x53);
    ADD_CRC_TO_LIST("CRC-7/UMTS", 7, 0x45, 0x0,  false, false, 0x0, 0x61);

    // CRC-8
    ADD_CRC_TO_LIST("CRC-8",            8, 0x7,  0x0,  false, false, 0x0,  0xF4);
    ADD_CRC_TO_LIST("CRC-8/AUTOSAR",    8, 0x2F, 0xFF, false, false, 0xFF, 0xDF);
    ADD_CRC_TO_LIST("CRC-8/CDMA2000",   8, 0x9B, 0xFF, false, false, 0x0,  0xDA);
    ADD_CRC_TO_LIST("CRC-8/DARC",       8, 0x39, 0x0,  true,  true,  0x0,  0x15);
    ADD_CRC_TO_LIST("CRC-8/DVB-S2",     8, 0xD5, 0x0,  false, false, 0x0,  0xBC);
    ADD_CRC_TO_LIST("CRC-8/EBU",        8, 0x1D, 0xFF, true,  true,  0x0,  0x97);
    ADD_CRC_TO_LIST("CRC-8/GSM-A",      8, 0x1D, 0x0,  false, false, 0x0,  0x37);
    ADD_CRC_TO_LIST("CRC-8/GSM-B",      8, 0x49, 0x0,  false, false, 0xFF, 0x94);
    ADD_CRC_TO_LIST("CRC-8/I-CODE",     8, 0x1D, 0xFD, false, false, 0x0,  0x7E);
    ADD_CRC_TO_LIST("CRC-8/ITU",        8, 0x7,  0x0,  false, false, 0x55, 0xA1);
    ADD_CRC_TO_LIST("CRC-8/LTE",        8, 0x9B, 0x0,  false, false, 0x0,  0xEA);
    ADD_CRC_TO_LIST("CRC-8/MAXIM",      8, 0x31, 0x0,  true,  true,  0x0,  0xA1);
    ADD_CRC_TO_LIST("CRC-8/OPENSAFETY", 8, 0x2F, 0x0,  false, false, 0x0,  0x3E);
    ADD_CRC_TO_LIST("CRC-8/ROHC",       8, 0x7,  0xFF, true,  true,  0x0,  0xD0);
    ADD_CRC_TO_LIST("CRC-8/WCDMA",      8, 0x9B, 0x0,  true,  true,  0x0,  0x25);

    // CRC-10
    ADD_CRC_TO_LIST("CRC-10",          10, 0x233, 0x0,   false, false, 0x0, 0x199);
    ADD_CRC_TO_LIST("CRC-10/CDMA2000", 10, 0x3D9, 0x3FF, false, false, 0x0, 0x233);

    // CRC-11
    ADD_CRC_TO_LIST("CRC-11", 11, 0x385, 0x1A, false, false, 0x0, 0x5A3);

    // CRC-12
    ADD_CRC_TO_LIST("CRC-12/3GPP",     12, 0x80F, 0x0,   false, true,  0x0, 0xDAF);
    ADD_CRC_TO_LIST("CRC-12/CDMA2000", 12, 0xF13, 0xFFF, false, false, 0x0, 0xD4D);
    ADD_CRC_TO_LIST("CRC-12/DECT",     12, 0x80F, 0x0,   false, false, 0x0, 0xF5B);

    // CRC-13
    ADD_CRC_TO_LIST("CRC-13/BBC", 13, 0x1CF5, 0x0, false, false, 0x0, 0x4FA);

    // CRC-14
    ADD_CRC_TO_LIST("CRC-14/DARC", 14, 0x805, 0x0, true, true, 0x0, 0x82D);

    // CRC-15
    ADD_CRC_TO_LIST("CRC-15",         15, 0x4599, 0x0, false, false, 0x0, 0x59E);
    ADD_CRC_TO_LIST("CRC-15/MPT1327", 15, 0x6815, 0x0, false, false, 0x1, 0x2566);

    // CRC-16
    ADD_CRC_TO_LIST("CRC-16/ARC",         16, 0x8005, 0x0,    true,  true,  0x0,    0xBB3D);
    ADD_CRC_TO_LIST("CRC-16/AUG-CCITT",   16, 0x1021, 0x1D0F, false, false, 0x0,    0xE5CC);
    ADD_CRC_TO_LIST("CRC-16/BUYPASS",     16, 0x8005, 0x0,    false, false, 0x0,    0xFEE8);
    ADD_CRC_TO_LIST("CRC-16/CCITT-FALSE", 16, 0x1021, 0xFFFF, false, false, 0x0,    0x29B1);
    ADD_CRC_TO_LIST("CRC-16/CDMA2000",    16, 0xC867, 0xFFFF, false, false, 0x0,    0x4C06);
    ADD_CRC_TO_LIST("CRC-16/DDS-110",     16, 0x8005, 0x800D, false, false, 0x0,    0x9ECF);
    ADD_CRC_TO_LIST("CRC-16/DECT-R",      16, 0x589,  0x0,    false, false, 0x1,    0x7E);
    ADD_CRC_TO_LIST("CRC-16/DECT-X",      16, 0x589,  0x0,    false, false, 0x0,    0x7F);
    ADD_CRC_TO_LIST("CRC-16/DNP",         16, 0x3D65, 0x0,    true,  true,  0xFFFF, 0xEA82);
    ADD_CRC_TO_LIST("CRC-16/EN-13757",    16, 0x3D65, 0x0,    false, false, 0xFFFF, 0xC2B7);
    ADD_CRC_TO_LIST("CRC-16/GENIBUS",     16, 0x1021, 0xFFFF, false, false, 0xFFFF, 0xD64E);
    ADD_CRC_TO_LIST("CRC-16/MAXIM",       16, 0x8005, 0x0,    true,  true,  0xFFFF, 0x44C2);
    ADD_CRC_TO_LIST("CRC-16/MCRF4XX",     16, 0x1021, 0xFFFF, true,  true,  0x0,    0x6F91);
    ADD_CRC_TO_LIST("CRC-16/RIELLO",      16, 0x1021, 0xB2AA, true,  true,  0x0,    0x63D0);
    ADD_CRC_TO_LIST("CRC-16/T10-DIF",     16, 0x8BB7, 0x0,    false, false, 0x0,    0xD0DB);
    ADD_CRC_TO_LIST("CRC-16/TELEDISK",    16, 0xA097, 0x0,    false, false, 0x0,    0xFB3);
    ADD_CRC_TO_LIST("CRC-16/TMS37157",    16, 0x1021, 0x89EC, true,  true,  0x0,    0x26B1);
    ADD_CRC_TO_LIST("CRC-16/USB",         16, 0x8005, 0xFFFF, true,  true,  0xFFFF, 0xB4C8);
    ADD_CRC_TO_LIST("CRC-A",              16, 0x1021, 0xC6C6, true,  true,  0x0,    0xBF05);
    ADD_CRC_TO_LIST("CRC-16/KERMIT",      16, 0x1021, 0x0,    true,  true,  0x0,    0x2189);
    ADD_CRC_TO_LIST("CRC-16/MODBUS",      16, 0x8005, 0xFFFF, true,  true,  0x0,    0x4B37);
    ADD_CRC_TO_LIST("CRC-16/X-25",        16, 0x1021, 0xFFFF, true,  true,  0xFFFF, 0x906E);
    ADD_CRC_TO_LIST("CRC-16/XMODEM",      16, 0x1021, 0x0,    false, false, 0x0,    0x31C3);

    // CRC-24
    ADD_CRC_TO_LIST("CRC-24",           24, 0x864CFB, 0xB704CE, false, false, 0x0, 0x21CF02);
    ADD_CRC_TO_LIST("CRC-24/FLEXRAY-A", 24, 0x5D6DCB, 0xFEDCBA, false, false, 0x0, 0x7979BD);
    ADD_CRC_TO_LIST("CRC-24/FLEXRAY-B", 24, 0x5D6DCB, 0xABCDEF, false, false, 0x0, 0x1F23B8);

    // CRC-31
    ADD_CRC_TO_LIST("CRC-31/PHILIPS", 31, 0x4C11DB7, 0x7FFFFFFF, false, false, 0x7FFFFFFF, 0xCE9E46C);

    // CRC-32
    ADD_CRC_TO_LIST("CRC-32",        32, 0x4C11DB7,  0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0xCBF43926);
    ADD_CRC_TO_LIST("CRC-32/BZIP2",  32, 0x4C11DB7,  0xFFFFFFFF, false, false, 0xFFFFFFFF, 0xFC891918);
    ADD_CRC_TO_LIST("CRC-32C",       32, 0x1EDC6F41, 0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0xE3069283);
    ADD_CRC_TO_LIST("CRC-32D",       32, 0xA833982B, 0xFFFFFFFF, true,  true,  0xFFFFFFFF, 0x87315576);
    ADD_CRC_TO_LIST("CRC-32/MPEG-2", 32, 0x4C11DB7,  0xFFFFFFFF, false, false, 0x0,        0x376E6E7 );
    ADD_CRC_TO_LIST("CRC-32/POSIX",  32, 0x4C11DB7,  0x0,        false, false, 0xFFFFFFFF, 0x765E7680);
    ADD_CRC_TO_LIST("CRC-32Q",       32, 0x814141AB, 0x0,        false, false, 0x0,        0x3010BF7F);
    ADD_CRC_TO_LIST("CRC-32/JAMCRC", 32, 0x4C11DB7,  0xFFFFFFFF, true,  true,  0x0,        0x340BC6D9);
    ADD_CRC_TO_LIST("CRC-32/XFER",   32, 0xAF,       0x0,        false, false, 0x0,        0xBD0BE338);

    // CRC-40
    ADD_CRC_TO_LIST("CRC-40/GSM", 40, 0x4820009, 0x0, false, false, 0xFFFFFFFFFF, 0xD4164FC646);

    // CRC-64
    ADD_CRC_TO_LIST("CRC-64",    64, 0x42F0E1EBA9EA3693, 0x0,                false, false, 0x0,                0x6C40DF5F0B497347);
    ADD_CRC_TO_LIST("CRC-64/WE", 64, 0x42F0E1EBA9EA3693, 0xFFFFFFFFFFFFFFFF, false, false, 0xFFFFFFFFFFFFFFFF, 0x62EC59E3F1A4F00A);
    ADD_CRC_TO_LIST("CRC-64/XZ", 64, 0x42F0E1EBA9EA3693, 0xFFFFFFFFFFFFFFFF, true,  true,  0xFFFFFFFFFFFFFFFF, 0x995DC9BBDF1939FA);

    return CRC_List;
}




const std::vector<AbstractProxy_CRC_t *> CRC_List = get_crc_list();




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


    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_bits() != CRC_List[i]->bits )
        {
            std::cout << "For CRC: " << CRC_List[i]->name <<  " bits must be: " << CRC_List[i]->bits << " but get: " << CRC_List[i]->get_bits() << "\n";
            return TEST_BROKEN;
        }
    }


    return TEST_PASSED;
}



int test_universal_crc_get_poly(struct test_info_t  *test_info)
{

    TEST_INIT;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_poly() != CRC_List[i]->poly )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << CRC_List[i]->name <<  " poly must be: " << CRC_List[i]->poly << " but get: " << CRC_List[i]->get_poly() << "\n";
            return TEST_BROKEN;
        }
    }


    return TEST_PASSED;
}



int test_universal_crc_get_init(struct test_info_t  *test_info)
{

    TEST_INIT;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_init() != CRC_List[i]->init )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << CRC_List[i]->name <<  " Init must be: " << CRC_List[i]->init << " but get: " << CRC_List[i]->get_init() << "\n";
            return TEST_BROKEN;
        }
    }


    return TEST_PASSED;
}



int test_universal_crc_get_xor_out(struct test_info_t  *test_info)
{

    TEST_INIT;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_xor_out() != CRC_List[i]->xor_out )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << CRC_List[i]->name <<  " Xor_out must be: " << CRC_List[i]->xor_out << " but get: " << CRC_List[i]->get_xor_out() << "\n";
            return TEST_BROKEN;
        }
    }


    return TEST_PASSED;
}



int test_universal_crc_get_ref_in(struct test_info_t  *test_info)
{

    TEST_INIT;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_ref_in() != CRC_List[i]->ref_in )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << CRC_List[i]->name <<  " ref_in must be: " << CRC_List[i]->ref_in << " but get: " << CRC_List[i]->get_ref_in() << "\n";
            return TEST_BROKEN;
        }
    }


    return TEST_PASSED;
}



int test_universal_crc_get_ref_out(struct test_info_t  *test_info)
{

    TEST_INIT;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        if( CRC_List[i]->get_ref_out() != CRC_List[i]->ref_out )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << CRC_List[i]->name <<  " ref_out must be: " << CRC_List[i]->ref_out << " but get: " << CRC_List[i]->get_ref_out() << "\n";
            return TEST_BROKEN;
        }
    }


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



int test_crc_std_check(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {

        crc = CRC_List[i]->get_crc("123456789", 9);

        if( crc != CRC_List[i]->check )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << CRC_List[i]->name <<  " std check: 0x" << CRC_List[i]->check << " but get: 0x" << crc << "\n";
            return TEST_BROKEN;
        }
    }


    return TEST_PASSED;
}



//------------- tests for Calculate CRC for file -------------



int test_crc_std_check_file(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;
    int res;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        crc = 0;
        res = CRC_List[i]->get_crc(crc, "std_file_to_test_crc");

        if( (res != 0) ||  (crc != CRC_List[i]->check) )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << CRC_List[i]->name <<  " std check: 0x" << CRC_List[i]->check << " but get: 0x" << crc << "\n";
            return TEST_BROKEN;
        }
    }


    return TEST_PASSED;
}



int test_crc_no_file(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;
    int res;


    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        crc = 0;
        res = CRC_List[i]->get_crc(crc, "");

        if( (res != -1) || (crc != 0) )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << CRC_List[i]->name <<  "no file but get_crc() ret:" << res << " crc:" << crc << "\n";
            return TEST_BROKEN;
        }
    }


    return TEST_PASSED;
}



//------------- tests for Calculate CRC for cunks -------------



int test_crc_for_cunks(struct test_info_t  *test_info)
{

    TEST_INIT;

    uint64_t crc;

    char buf[]  = "1234";
    char buf2[] = "56789";


    for( size_t i = 0; i < CRC_List.size(); i++)
    {
        crc = CRC_List[i]->get_crc_init();
        crc = CRC_List[i]->get_raw_crc(buf,  4, crc);
        crc = CRC_List[i]->get_raw_crc(buf2, 5, crc);
        crc = CRC_List[i]->get_final_crc(crc);

        if( crc != CRC_List[i]->check )
        {
            std::cout << std::hex;
            std::cout << "For CRC: " << CRC_List[i]->name <<  " std check: 0x" << CRC_List[i]->check << " but get: 0x" << crc << "\n";
            return TEST_BROKEN;
        }
    }


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
    test_crc_std_check,

    test_crc_std_check_file,
    test_crc_no_file,

    test_crc_for_cunks,
};



int main(void)
{

    RUN_TESTS(tests);

    return 0;
}
