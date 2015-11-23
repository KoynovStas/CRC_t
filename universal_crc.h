/*
 * universal_crc.h
 *
 *
 * Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 *  1 Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  2 Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  3 Neither the name of the <organization> nor the
 *    names of its contributors may be used to endorse or promote products
 *   derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL <COPYRIGHT HOLDER> BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */

#ifndef UNIVERSAL_CRC_H
#define UNIVERSAL_CRC_H

#include <stdint.h>
#include <string>
#include <cstdio>





template<uint8_t Bits_minus_1_div_8> struct CRC_Type_helper{ typedef uint64_t value_type; }; // default

template<> struct CRC_Type_helper<0> { typedef uint8_t  value_type; }; //for Bits 1..8
template<> struct CRC_Type_helper<1> { typedef uint16_t value_type; }; //for Bits 9..16
template<> struct CRC_Type_helper<2> { typedef uint32_t value_type; }; //for Bits 17..24
template<> struct CRC_Type_helper<3> { typedef uint32_t value_type; }; //for Bits 25..32


#define CRC_TYPE typename CRC_Type_helper< (Bits-1)/8 >::value_type





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
class Universal_CRC
{


    public:

        typedef CRC_TYPE CRC_Type;

        explicit Universal_CRC(const std::string crc_name = "");


        std::string name;

        uint8_t   get_bits()    const { return Bits;  }
        CRC_Type  get_poly()    const { return Poly;  }
        CRC_Type  get_init()    const { return Init;  }
        CRC_Type  get_xor_out() const { return XorOut;}
        bool      get_ref_in()  const { return RefIn; }
        bool      get_ref_out() const { return RefOut;}

        CRC_Type  get_crc_init()const { return init;    } //init = reflect(Init, Bits) if RefIn, else = Init
        CRC_Type  get_top_bit() const { return top_bit; }
        CRC_Type  get_crc_mask()const { return crc_mask;}

        CRC_Type get_crc(const char* buf, size_t len);
        CRC_Type get_crc(CRC_Type crc, const char* buf, size_t len); //for first byte crc = init (must be)

        int get_crc(CRC_Type *crc, const char *file_name);


    private:

        CRC_Type reflect(CRC_Type data, uint8_t num_bits);
        void init_crc_table();

        uint8_t  shift;
        CRC_Type init;
        CRC_Type top_bit;
        CRC_Type crc_mask;
        CRC_Type crc_table[256];
};





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
Universal_CRC<Bits, Poly, Init, RefIn, RefOut, XorOut>::Universal_CRC(const std::string crc_name) :
    name(crc_name)
{

    top_bit  = (CRC_Type)1 << (Bits - 1);
    crc_mask = ( (top_bit - 1) << 1) | 1;


    if(Bits > 8)
        shift = (Bits - 8);
    else
        shift = (8 - Bits);


    if(RefIn)
        init = reflect(Init, Bits);
    else
        init = Init;


    init_crc_table();
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE Universal_CRC<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_crc(const char* buf, size_t len)
{

    CRC_Type crc = get_crc(init, buf, len);

    if(RefOut^RefIn) crc = reflect(crc, Bits);

    crc ^= XorOut;
    crc &= crc_mask; //for CRC not power 2

    return crc;
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE Universal_CRC<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_crc(CRC_Type crc, const char* buf, size_t len)
{

    if(Bits > 8)
    {
        if(RefIn)
            while (len--)
                crc = (crc >> 8) ^ crc_table[ (crc ^ *buf++) & 0xff ];
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
int Universal_CRC<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_crc(CRC_Type *crc, const char *file_name)
{

    if( !file_name || !crc )
        return -1; //Bad param

    *crc = init;

    char buf[4096];


    FILE *stream = fopen(file_name, "rb");
    if( stream == NULL )
        return -1; //Cant open file


    while( !feof(stream) )
    {
       size_t len = fread(buf, 1, sizeof(buf), stream);
       *crc = get_crc(*crc, buf, len);
    }


    fclose(stream);


    if(RefOut^RefIn) *crc = reflect(*crc, Bits);

    *crc ^= XorOut;
    *crc &= crc_mask; //for CRC not power 2


    return 0; //good  job
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE Universal_CRC<Bits, Poly, Init, RefIn, RefOut, XorOut>::reflect(CRC_Type data, uint8_t num_bits)
{

    CRC_Type reflection = 0;
    CRC_Type one = 1;

    for ( size_t i = 0; i < num_bits; ++i, data >>= 1 )
    {
        if ( data & one )
        {
            reflection |= ( one << (num_bits - one - i) );
        }
    }

    return reflection;
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
void Universal_CRC<Bits, Poly, Init, RefIn, RefOut, XorOut>::init_crc_table()
{
    int i;
    CRC_Type crc;


    for(i = 0; i < 256; i++)
    {

        crc = 0;

        for(uint8_t mask = 0x80; mask; mask >>= 1)
        {

            if ( i & mask )
                crc ^= top_bit;


            if (crc & top_bit)
            {
                crc <<= 1;
                crc ^= Poly;
            }
            else
                crc <<= 1;
        }

        crc &= crc_mask; //for CRC not power 2

        if(RefIn)
            crc_table[reflect(i, 8)] = reflect(crc, Bits);
        else
            crc_table[i] = crc;
     }
}





#endif // UNIVERSAL_CRC_H
