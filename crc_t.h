/*
 * crc_t.h
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

#ifndef CRC_T_H
#define CRC_T_H

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
class CRC_t
{


    public:

        typedef CRC_TYPE CRC_Type;

        explicit CRC_t(const std::string crc_name = "");


        std::string name;

        // get param CRC
        uint8_t  get_bits()    const { return Bits;  }
        CRC_Type get_poly()    const { return Poly;  }
        CRC_Type get_init()    const { return Init;  }
        CRC_Type get_xor_out() const { return XorOut;}
        bool     get_ref_in()  const { return RefIn; }
        bool     get_ref_out() const { return RefOut;}

        CRC_Type get_crc_init()const { return init;    } //init = reflect(Init, Bits) if RefIn, else = Init
        CRC_Type get_top_bit() const { return top_bit; }
        CRC_Type get_crc_mask()const { return crc_mask;}


        // Calculate methods
        CRC_Type get_crc(const char* buf, size_t len) const;
        int      get_crc(CRC_Type *crc, const char *file_name) const;


        // Calculate for chunks of data
        CRC_Type get_raw_crc(const char* buf, size_t len, CRC_Type crc) const; //for first byte crc = init (must be)
        CRC_Type get_final_crc(CRC_Type raw_crc) const;



    private:

        CRC_Type reflect(CRC_Type data, uint8_t num_bits) const;
        void init_crc_table();

        uint8_t  shift;
        CRC_Type init;
        CRC_Type top_bit;
        CRC_Type crc_mask;
        CRC_Type crc_table[256];
};





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::CRC_t(const std::string crc_name) :
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
CRC_TYPE CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_crc(const char* buf, size_t len) const
{

    CRC_Type crc = get_raw_crc(buf, len, init);

    return get_final_crc(crc);
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
int CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_crc(CRC_Type *crc, const char *file_name) const
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
       *crc = get_raw_crc(buf, len, *crc);
    }


    fclose(stream);


    *crc = get_final_crc(*crc);


    return 0; //good  job
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_raw_crc(const char* buf, size_t len, CRC_Type crc) const
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
CRC_TYPE CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::get_final_crc(CRC_Type raw_crc) const
{

    if(RefOut^RefIn) raw_crc = reflect(raw_crc, Bits);

    raw_crc ^= XorOut;
    raw_crc &= crc_mask; //for CRC not power 2

    return raw_crc;
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::reflect(CRC_Type data, uint8_t num_bits) const
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
void CRC_t<Bits, Poly, Init, RefIn, RefOut, XorOut>::init_crc_table()
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





#endif // CRC_T_H
