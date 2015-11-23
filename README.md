# Universal_CRC - is C++ template for calculation CRC sizes 1-64 bits


## Description

Universal_CRC is C++ template for calculation CRC sizes 1-64 bits.

#### Features of the implementation:

 -  The code uses only the standard **C++03 not C++11** -> This allows you to use the template in the oldest projects with older compilers.
 - In the code not uses the library boost.
 - The code has no dependencies, and imprisoned in the one file.
 - For **any** bit-depth (width) of CRC will be use the standard table method for calculation. Will be calculated standart table for byte (table size 256 elements)


Template parameters is the standard Specifications algorithms CRC as described in Ross N. Williams [A PAINLESS GUIDE TO CRC ERROR DETECTION ALGORITHMS.](http://www.ross.net/crc/download/crc_v3.txt)


**Ross N. Williams:**

> By putting all these pieces together we end up with the parameters of the algorithm:
>
>   - **NAME:** This is a name given to the algorithm. A string value.
>
>   - **WIDTH:** This is the width of the algorithm expressed in bits.
>   This is one less than the width of the Poly.
>
>   - **POLY:** This parameter is the poly. This is a binary value that
>   should be specified as a hexadecimal number. The top bit of the
>   poly should be omitted. For example, if the poly is 10110, you
>   should specify 06. An important aspect of this parameter is that it
>   represents the unreflected poly; the bottom bit of this parameter
>   is always the LSB of the divisor during the division regardless of
>   whether the algorithm being modelled is reflected.
>
>   - **INIT:** This parameter specifies the initial value of the register
>   when the algorithm starts. This is the value that is to be assigned
>   to the register in the direct table algorithm. In the table
>   algorithm, we may think of the register always commencing with the
>   value zero, and this value being XORed into the register after the
>   N'th bit iteration. This parameter should be specified as a
>   hexadecimal number.
>
>   - **REFIN:** This is a boolean parameter. If it is FALSE, input bytes are
>   processed with bit 7 being treated as the most significant bit
>   (MSB) and bit 0 being treated as the least significant bit. If this
>   parameter is FALSE, each byte is reflected before being processed.>
>
>   - **REFOUT:** This is a boolean parameter. If it is set to FALSE, the
>   final value in the register is fed into the XOROUT stage directly,
>   otherwise, if this parameter is TRUE, the final register value is
>   reflected first.
>
>   - **XOROUT:** This is an W-bit value that should be specified as a
>   hexadecimal number. It is XORed to the final register value (after
>   the REFOUT) stage before the value is returned as the official
>   checksum.
>
>   - **CHECK:** This field is not strictly part of the definition, and, in
>   the event of an inconsistency between this field and the other
>   field, the other fields take precedence. This field is a check
>   value that can be used as a weak validator of implementations of
>   the algorithm. The field contains the checksum obtained when the
>   ASCII string "123456789" is fed through the specified algorithm
>   (i.e. 313233... (hexadecimal)).



**Template Universal_CRC has the following parameters:**
```C++
template <uint8_t Bits, CRC_TYPE Poly, CRC_TYPE Init, bool RefIn, bool RefOut, CRC_TYPE XorOut>
```


**The class has the following public methods:**
```C++
typedef CRC_TYPE CRC_Type;

explicit Universal_CRC(const std::string crc_name = "");


std::string name;

uint8_t  get_bits()    const { return Bits;  }
CRC_Type get_poly()    const { return Poly;  }
CRC_Type get_init()    const { return Init;  }
CRC_Type get_xor_out() const { return XorOut;}
bool     get_ref_in()  const { return RefIn; }
bool     get_ref_out() const { return RefOut;}

CRC_Type get_crc_init()const { return init;    } //init = reflect(Init, Bits) if RefIn, else = Init
CRC_Type get_top_bit() const { return top_bit; }
CRC_Type get_crc_mask()const { return crc_mask;}

CRC_Type get_crc(const char* buf, size_t len);
int      get_crc(CRC_Type *crc, const char *file_name);

//for chunks of data
CRC_Type get_raw_crc(CRC_Type crc, const char* buf, size_t len); //for first byte crc = init (must be)
CRC_Type get_final_crc(CRC_Type raw_crc);
```

More details see: **[universal_crc.h](./universal_crc.h)**

<br/>
## Usage

**To start working, perform the following steps:**

1. You need to include **[universal_crc.h](./universal_crc.h)** file in your **.cpp** file.
2. Parameterize a template (see an examples)

<br/>
## Examples

**Get CRC32 for file:**

```C++
uint32_t crc;

Universal_CRC<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

int res = ucrc.get_crc(&crc, "standard_check_file"); // res == -1 (error); res == 0 (good)

if( res != -1 )
    //uses crc
```

**Get CRC32 for single buf:**

```C++
char buf[len_of_buf]; //bla bla

uint32_t crc;

Universal_CRC<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

crc = ucrc.get_crc(buf, len_of_buf);
//uses crc
```

**Get CRC32 for buf(s) (chunks):**

**Note:**
when the method is used CRC_Type get_raw_crc(CRC_Type crc, const char* buf, size_t len)
for the first byte (or chunk of data) **crc** param must be obtained through a method **get_crc_init()** and in the final you need to call the method: **get_final_crc():**

```C++
char buf[len_of_buf];   //bla bla
char buf2[len_of_buf2]; //bla bla

uint32_t crc;

Universal_CRC<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

crc = ucrc.get_crc_init();
crc = ucrc.get_raw_crc(crc, buf,  len_of_buf);   //first chunk
crc = ucrc.get_raw_crc(crc, buf2, len_of_buf2);  //second chunk
crc = get_final_crc(crc);
//uses crc
```

More details can be found in the test application: **[crc_test.cpp](./crc_test.cpp)**


<br/>
## License

[BSD](./LICENSE).
