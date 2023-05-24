/*
 * CRC_t is C++ template for calculation CRC any sizes(width) 1-64 bits.
 *
 *
 * version 3.0
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

#include <cstdint>
#include <cerrno>
#include <fstream>    // for std::ifstream
#include <ios>        // for std::ios_base, etc.





template<uint8_t Bits_minus_1_div_8> struct CRC_Type_helper{ using value_type = uint64_t; }; // default

template<> struct CRC_Type_helper<0> { using value_type = uint8_t;  }; //for Bits 1..8
template<> struct CRC_Type_helper<1> { using value_type = uint16_t; }; //for Bits 9..16
template<> struct CRC_Type_helper<2> { using value_type = uint32_t; }; //for Bits 17..24
template<> struct CRC_Type_helper<3> { using value_type = uint32_t; }; //for Bits 25..32


#define CRC_TYPE typename CRC_Type_helper< (Bits-1)/8 >::value_type





/*
 * CRCBase_t - is the base class that we will use in various algorithms.
 * This class accepts an Impl template parameter (use Curiously Recurring Template Pattern (CRTP)).
 * This allows us to use the get_raw_crc_impl() method from the implementation class without using virtual methods.
 */
template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
class CRCBase_t
{
    static_assert((Bits >= 1) && (Bits <= 64), "Bits must be in the range [1,64]");


    public:
        using CRC_Type = CRC_TYPE;

        // get param CRC
        static constexpr uint8_t  get_bits()    noexcept { return Bits;  }
        static constexpr CRC_Type get_poly()    noexcept { return Poly;  }
        static constexpr CRC_Type get_init()    noexcept { return Init;  }
        static constexpr CRC_Type get_xor_out() noexcept { return XorOut;}
        static constexpr bool     get_ref_in()  noexcept { return RefIn; }
        static constexpr bool     get_ref_out() noexcept { return RefOut;}

        static constexpr CRC_Type get_top_bit() noexcept { return (CRC_Type)1 << (Bits - 1);         }
        static constexpr CRC_Type get_crc_mask()noexcept { return ( (get_top_bit() - 1) << 1) | 1;   }
        static constexpr CRC_Type get_crc_init()noexcept { return RefIn ? reflect(Init, Bits) : Init;}

        CRC_Type get_check() const noexcept;//crc for ASCII string "123456789" (3132..39(in hex))

        // Calculate methods
        CRC_Type get_crc(const void* data, size_t len) const noexcept;
        int      get_crc(CRC_Type &crc, const char* file_name) const noexcept;
        int      get_crc(CRC_Type &crc, const char* file_name, void* buf, size_t size_buf) const noexcept;

        // Calculate for chunks of data
        CRC_Type get_raw_crc(const void* data, size_t len) const noexcept;                   //get raw_crc for first chunk of data
        CRC_Type get_raw_crc(const void* data, size_t len, CRC_Type raw_crc) const noexcept; //get raw_crc for chunk of data
        static constexpr CRC_Type get_end_crc(CRC_Type raw_crc) noexcept;


    protected:
        static constexpr CRC_Type reflect(CRC_Type data, uint8_t num_bits) noexcept;

        static CRC_Type get_raw_normal_crc   (uint8_t byte) noexcept;
        static CRC_Type get_raw_reflected_crc(uint8_t byte) noexcept;


    private:
        int get_crc(CRC_Type &crc, std::ifstream& ifs, void* buf, size_t size_buf) const noexcept;
};





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
CRC_TYPE CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::get_check() const noexcept
{
    const uint8_t data[] = {0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39};

    return get_crc(data, sizeof(data));
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
CRC_TYPE CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::
get_crc(const void* data, size_t len) const noexcept
{
    CRC_Type crc = get_raw_crc(data, len, get_crc_init());

    return get_end_crc(crc);
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
int CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::
get_crc(CRC_Type &crc, const char *file_name) const noexcept
{
    char buf[4096];

    return get_crc(crc, file_name, buf, sizeof(buf));
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
int CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::
get_crc(CRC_Type &crc, const char* file_name, void* buf, size_t size_buf) const noexcept
{
    std::ifstream ifs(file_name, std::ios_base::binary);

    if( !ifs || !buf || !size_buf)
    {
        errno = EINVAL;
        return -1;
    }

    return get_crc(crc, ifs, buf, size_buf);
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
int CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::
get_crc(CRC_Type &crc, std::ifstream& ifs, void* buf, size_t size_buf) const noexcept
{
    crc = get_crc_init();

    while( ifs )
    {
        ifs.read(static_cast<char *>(buf), size_buf);
        crc = get_raw_crc(buf, ifs.gcount(), crc);
    }

    crc = get_end_crc(crc);

    return (ifs.rdstate() & std::ios_base::badbit);  //return 0 if all good
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
CRC_TYPE CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::
get_raw_crc(const void* data, size_t len) const noexcept
{
    return get_raw_crc(data, len, get_crc_init());
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
CRC_TYPE CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::
get_raw_crc(const void* data, size_t len, CRC_Type raw_crc) const noexcept
{
    //use Curiously Recurring Template Pattern (CRTP)
    return static_cast<const Impl*>(this)->get_raw_crc_impl(data, len, raw_crc);
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
constexpr CRC_TYPE CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::
get_end_crc(CRC_Type raw_crc) noexcept
{
    if(RefOut^RefIn)
        raw_crc = reflect(raw_crc, Bits);

    raw_crc ^= XorOut;
    raw_crc &= get_crc_mask(); //for CRC not a multiple of a byte (8 bits)

    return raw_crc;
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
constexpr CRC_TYPE CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::
reflect(CRC_Type data, uint8_t num_bits) noexcept
{
    CRC_Type reflection = 0;

    while( num_bits-- )
    {
        reflection = (reflection << 1) | (data & 1);
        data >>= 1;
    }

    return reflection;
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
CRC_TYPE CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::get_raw_normal_crc(uint8_t byte) noexcept
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

    return crc & get_crc_mask(); //for CRC not a multiple of a byte (8 bits);
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut, class Impl>
CRC_TYPE CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut, Impl>::get_raw_reflected_crc(uint8_t byte) noexcept
{
    constexpr CRC_Type ref_poly = reflect(Poly, Bits);

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

    return crc;
}





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
class CRCImplTable8: public CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut,
                                      CRCImplTable8<Bits, Poly, Init, RefIn, RefOut, XorOut> >
{
    public:
        using CRC_Type = CRC_TYPE;

        CRCImplTable8() noexcept { init_crc_table(); }

        CRC_Type get_raw_crc_impl(const void* data, size_t len, CRC_Type crc) const noexcept;


    private:
        CRC_Type crc_table[256];

        void     init_crc_table() noexcept;
};





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE CRCImplTable8<Bits, Poly, Init, RefIn, RefOut, XorOut>::
get_raw_crc_impl(const void* data, size_t len, CRC_Type crc) const noexcept
{
    auto buf = static_cast< const uint8_t* >(data);

    constexpr int shift = (Bits > 8) ? (Bits - 8) : (8 - Bits);


    if(Bits > 8)
    {
        if(RefIn)
            while (len--)
                crc = (crc >> 8) ^ crc_table[(crc ^ *buf++) & 0xff];
        else
            while (len--)
                crc = (crc << 8) ^ crc_table[((crc >> shift) ^ *buf++) & 0xff];
    }
    else
    {
        if(RefIn)
            while (len--)
                crc = crc_table[crc ^ *buf++];
        else
            while (len--)
                crc = crc_table[(crc << shift) ^ *buf++];
    }


    return crc;
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
void CRCImplTable8<Bits, Poly, Init, RefIn, RefOut, XorOut>::init_crc_table() noexcept
{
    //Calculation of the CRC table for byte.
    for(int byte = 0; byte < 256; byte++)
    {
        if(RefIn)
            crc_table[byte] = this->get_raw_reflected_crc(byte); // Reflected CRC table for byte.
        else
            crc_table[byte] = this->get_raw_normal_crc(byte);    // Normal CRC table for byte.
    }
}





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
class CRCImplBits: public CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut,
                                    CRCImplBits<Bits, Poly, Init, RefIn, RefOut, XorOut> >
{
    public:
        using CRC_Type = CRC_TYPE;

        CRC_Type get_raw_crc_impl(const void* data, size_t len, CRC_Type crc) const noexcept;
};





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE CRCImplBits<Bits, Poly, Init, RefIn, RefOut, XorOut>::
get_raw_crc_impl(const void* data, size_t len, CRC_Type crc) const noexcept
{
    auto buf = static_cast< const uint8_t* >(data);

    constexpr int shift = (Bits > 8) ? (Bits - 8) : (8 - Bits);


    if(Bits > 8)
    {
        if(RefIn)
            while (len--)
                crc = (crc >> 8) ^ this->get_raw_reflected_crc((crc ^ *buf++) & 0xff);
        else
            while (len--)
                crc = (crc << 8) ^ this->get_raw_normal_crc(((crc >> shift) ^ *buf++) & 0xff);
    }
    else
    {
        if(RefIn)
            while (len--)
                crc = this->get_raw_reflected_crc(crc ^ *buf++);
        else
            while (len--)
                crc = this->get_raw_normal_crc((crc << shift) ^ *buf++);
    }

    return crc;
}





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
class CRCImplTable4: public CRCBase_t<Bits, Poly, Init, RefIn, RefOut, XorOut,
                                      CRCImplTable4<Bits, Poly, Init, RefIn, RefOut, XorOut> >
{
    public:
        using CRC_Type = CRC_TYPE;

        CRCImplTable4() noexcept { init_crc_table(); };

        CRC_Type get_raw_crc_impl(const void* data, size_t len, CRC_Type crc) const noexcept;


    private:
        CRC_Type crc_table[16];

        void     init_crc_table() noexcept;
};





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
CRC_TYPE CRCImplTable4<Bits, Poly, Init, RefIn, RefOut, XorOut>::
get_raw_crc_impl(const void* data, size_t len, CRC_Type crc) const noexcept
{
    auto buf = static_cast< const uint8_t* >(data);

    constexpr int shift = (Bits > 4) ? (Bits - 4) : (4 - Bits);


    if(Bits > 4)
    {
        if(RefIn)
            while (len--)
            {
                crc = crc_table[(crc ^ *buf       ) & 0x0f] ^ (crc >> 4);
                crc = crc_table[(crc ^ (*buf >> 4)) & 0x0f] ^ (crc >> 4);
                buf++;
            }
        else
            while (len--)
            {
                crc = crc_table[((crc >> shift) ^ (*buf >> 4)) & 0x0f] ^ (crc << 4);
                crc = crc_table[((crc >> shift) ^ *buf       ) & 0x0f] ^ (crc << 4);
                buf++;
            }
    }
    else//Bits <= 4
    {
        if(RefIn)
            while (len--)
            {
                crc = crc_table[(crc ^ *buf       ) & 0x0f];
                crc = crc_table[(crc ^ (*buf >> 4)) & 0x0f];
                buf++;
            }
        else
            while (len--)
            {
                crc = crc_table[((crc << shift) ^ (*buf >> 4)) & 0x0f];
                crc = crc_table[((crc << shift) ^ *buf       ) & 0x0f];
                buf++;
            }
    }

    return crc;
}



template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
void CRCImplTable4<Bits, Poly, Init, RefIn, RefOut, XorOut>::init_crc_table() noexcept
{
    //Calculation of the CRC table for half byte.
    for(int byte = 0; byte < 16; byte++)
    {
        if(RefIn)
            crc_table[byte] = this->get_raw_reflected_crc(byte*16); //see note1
        else
            crc_table[byte] = this->get_raw_normal_crc(byte);
    }

    //note1: *16 it's equivalent function for calculating CRC for 4 bits (the result of symmetry)
}





template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut,
          template<uint8_t, CRC_TYPE, CRC_TYPE, bool, bool, CRC_TYPE> class Impl = CRCImplTable8>
class CRC_t: public Impl<Bits, Poly, Init, RefIn, RefOut, XorOut>
{
};





#endif // CRC_T_H
