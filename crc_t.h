/*
 * crc_t.h
 *
 *
 * version 1.2
 *
 *
 *
 * BSD 3-Clause License
 *
 * Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru
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

#ifndef CRC_T_H
#define CRC_T_H

#include <stdint.h>
#include <errno.h>
#include <fstream>    // for std::ifstream
#include <ios>        // for std::ios_base, etc.






// For GCC 4.6 or higher, in C++ you can use a standard
// static_assert(exp, msg) in *.c and in *.h files.
// For GCC 4.6 is required to add CFLAGS += -std="c++0x"
// A lot of variants, it is the most simple and intuitive
// It can be used in *.c and in *.h files.
// (macros that use function style can be used in *.c files only)
//
// Disadvantages: you can not be set msg to display the console when compiling
//
// Example:
//
//  CRC_STATIC_ASSERT( sizeof(char) == 1)  //good job
//  CRC_STATIC_ASSERT( sizeof(char) != 1)  //You will get a compilation error
//
#define CRC_ASSERT_CONCAT_(a, b) a##b
#define CRC_ASSERT_CONCAT(a, b) CRC_ASSERT_CONCAT_(a, b)
#define CRC_STATIC_ASSERT(expr) \
    enum { CRC_ASSERT_CONCAT(assert_line_, __LINE__) = 1/(int)(!!(expr)) }










template<uint8_t Bits_minus_1_div_8> struct CRC_Type_helper{ typedef uint64_t value_type; }; // default

template<> struct CRC_Type_helper<0> { typedef uint8_t  value_type; }; //for Bits 1..8
template<> struct CRC_Type_helper<1> { typedef uint16_t value_type; }; //for Bits 9..16
template<> struct CRC_Type_helper<2> { typedef uint32_t value_type; }; //for Bits 17..24
template<> struct CRC_Type_helper<3> { typedef uint32_t value_type; }; //for Bits 25..32


#define CRC_TYPE typename CRC_Type_helper< (Bits-1)/8 >::value_type





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
class CRC_t
{
    CRC_STATIC_ASSERT(Bits >= 1);
    CRC_STATIC_ASSERT(Bits <= 64);


    public:

        typedef CRC_TYPE CRC_Type;

        CRC_t();


        // get param CRC
        uint8_t  get_bits()    const { return Bits;  }
        CRC_Type get_poly()    const { return Poly;  }
        CRC_Type get_init()    const { return Init;  }
        CRC_Type get_xor_out() const { return XorOut;}
        bool     get_ref_in()  const { return RefIn; }
        bool     get_ref_out() const { return RefOut;}

        CRC_Type get_top_bit() const { return (CRC_Type)1 << (Bits - 1);      }
        CRC_Type get_crc_mask()const { return ( (get_top_bit() - 1) << 1) | 1;}
        CRC_Type get_crc_init()const { return crc_init;} //crc_init = reflect(Init, Bits) if RefIn, else = Init
        CRC_Type get_check()   const;                    //crc for ASCII string "123456789" (i.e. 313233... (hexadecimal)).


        // Calculate methods
        CRC_Type get_crc(const void* data, size_t len) const;
        int      get_crc(CRC_Type &crc, const char* file_name) const;
        int      get_crc(CRC_Type &crc, const char* file_name, void* buf, size_t size_buf) const;


        // Calculate for chunks of data
        CRC_Type get_raw_crc(const void* data, size_t len, CRC_Type crc) const; //for first byte crc = init (must be)
        CRC_Type get_end_crc(CRC_Type raw_crc) const;



    private:

        CRC_Type crc_init;
        CRC_Type crc_table[256];


        CRC_Type reflect(CRC_Type data, uint8_t num_bits) const;
        void     init_normal_crc_table();
        void     init_reflected_crc_table();

        int      get_crc(CRC_Type &crc, std::ifstream& ifs, void* buf, size_t size_buf) const;
};





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::CRC_t()
{

    if(RefIn)
    {
        crc_init = reflect(Init, Bits);
        init_reflected_crc_table();
    }
    else
    {
        crc_init = Init;
        init_normal_crc_table();
    }
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_check() const
{
    const uint8_t data[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

    return get_crc(data, sizeof(data));
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_crc(const void* data, size_t len) const
{
    CRC_Type crc = get_raw_crc(data, len, crc_init);

    return get_end_crc(crc);
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
int CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_crc(CRC_Type &crc, const char *file_name) const
{
    char buf[4096];

    return get_crc(crc, file_name, buf, sizeof(buf));
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
int CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_crc(CRC_Type &crc, const char* file_name, void* buf, size_t size_buf) const
{
    std::ifstream ifs(file_name, std::ios_base::binary);

    if( !ifs || !buf || !size_buf)
    {
        errno = EINVAL;
        return -1;
    }

    return get_crc(crc, ifs, buf, size_buf);
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
int CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_crc(CRC_Type &crc, std::ifstream& ifs, void* buf, size_t size_buf) const
{
    crc = crc_init;

    while( ifs )
    {
        ifs.read(static_cast<char *>(buf), size_buf);
        crc = get_raw_crc(buf, ifs.gcount(), crc);
    }

    crc = get_end_crc(crc);

    return (ifs.rdstate() & std::ios_base::badbit);  //return 0 if all good
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_raw_crc(const void* data, size_t len, CRC_Type crc) const
{
    const uint8_t* buf = static_cast< const uint8_t* >(data);

    uint8_t shift;

    if(Bits > 8)
        shift = (Bits - 8);
    else
        shift = (8 - Bits);


    if(Bits > 8)
    {
        if(RefIn)
            while (len--)
                crc = (crc >> 8) ^ crc_table[ (crc & 0xff) ^ *buf++];
        else
            while (len--)
                crc = (crc << 8) ^ crc_table[ ((crc >> shift) & 0xff) ^ *buf++ ];
    }
    else
    {
        if (RefIn)
            while (len--)
                crc = crc_table[ crc ^ *buf++ ];
        else
            while (len--)
                crc = crc_table[ (crc << shift) ^ *buf++ ];
    }


    return crc;
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_end_crc(CRC_Type raw_crc) const
{
    if(RefOut^RefIn)
        raw_crc = reflect(raw_crc, Bits);

    raw_crc ^= XorOut;
    raw_crc &= get_crc_mask(); //for CRC not a multiple of a byte (8 bits)

    return raw_crc;
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::reflect(CRC_Type data, uint8_t num_bits) const
{
    CRC_Type reflection = 0;

    while( num_bits-- )
    {
        reflection = (reflection << 1) | (data & 1);
        data >>= 1;
    }

    return reflection;
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
void CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::init_normal_crc_table()
{
    //Calculation of the Normal CRC table for byte.
    for(int byte = 0; byte < 256; byte++)
    {

        CRC_Type crc = 0;

        for(int bit = 0x80; bit; bit >>= 1)
        {

            if( byte & bit )
                crc ^= get_top_bit();


            if( crc & get_top_bit() )
            {
                crc <<= 1;
                crc ^= Poly;
            }
            else
                crc <<= 1;
        }

        crc &= get_crc_mask(); //for CRC not a multiple of a byte (8 bits)
        crc_table[byte] = crc;
     }
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
void CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::init_reflected_crc_table()
{
    //Calculation of the Reflected CRC table for byte.
    CRC_Type ref_poly = reflect(Poly, Bits);

    for(int byte = 0; byte < 256; byte++)
    {

        CRC_Type crc = byte;

        for(int bit = 0x80; bit; bit >>= 1)
        {

            if( crc & 1 )
            {
                crc >>= 1;
                crc ^= ref_poly;
            }
            else
                crc >>= 1;
        }

        crc_table[byte] = crc;
    }
}





#endif // CRC_T_H
