# CRC_t - is C++ template for calculation CRC any sizes 1-64 bits


## Description

`CRC_t` is C++ template for calculation CRC any sizes(width) 1-64 bits.

#### Features of the implementation:

 - The code has no dependencies, and imprisoned in the one file.
 - The code uses only the standard **C++03** -> This allows you to use the template in the oldest projects with older compilers.
 - The following implementations are supported:
    * **CRCImplBits** - loop for 8 bits in byte (no table)
    * **CRCImplTable4** - table for half byte (16 elements)
    * **CRCImplTable8** - std table for byte (256 elements)
 - All the parameters of CRC passed as template parameters. This allows the compiler to make a very strong optimization. Example ModBus-CRC for architecture ARMv7 (GCC 4.9.2) calculate CRC for a buffer(array) will loop from 9 commands in assembler.


#### Limitations of the implementation:

- After the parameterization of the template, you cannot change the parameters of the CRC.


If you need a class to work with different CRC algorithms, which can change the algorithm parameters in the dynamics (Run-Time) see:
[uCRC_t](https://github.com/KoynovStas/uCRC_t)


Template parameters is the standard Specifications algorithms CRC as described in Ross N. Williams [A PAINLESS GUIDE TO CRC ERROR DETECTION ALGORITHMS](./doc/crc_v3.txt)


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



**Template CRC_t has the following parameters:**
```C++
template <Bits, Poly, Init, RefIn, RefOut, XorOut, Impl = CRCImplTable8>
```


**The class has the following public methods:**
```C++
typedef CRC_TYPE CRC_Type;

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
CRC_Type get_raw_crc(const void* data, size_t len) const;                   //get raw_crc for first chunk of data
CRC_Type get_raw_crc(const void* data, size_t len, CRC_Type raw_crc) const; //get raw_crc for chunk of data
CRC_Type get_end_crc(CRC_Type raw_crc) const;
```

More details see: **[crc_t.h](./crc_t.h)**


## Usage

**To start working, perform the following steps:**

1. You need to include **[crc_t.h](./crc_t.h)** file in your **.cpp** file.
2. Parameterize a template (see an examples)

**Note:**
> The parameters for the template correspond to the `Ross N. Williams` specification. A list of CRC algorithms for this specification can be found here: [Catalogue CRC algorithms](http://reveng.sourceforge.net/crc-catalogue/all.htm)


Since from version 2.0 you can choose a different calculation algorithm.
The default implementation parameter is `Impl = CRCImplTable8`.
You can select the following algorithm:
* **CRCImplBits** - loop for 8 bits in byte (no table)
* **CRCImplTable4** - table for half byte (16 elements)
* **CRCImplTable8** - std table for byte (256 elements)

Result of speed test: [benchmark.md](./tests/benchmark.md)


## Examples

**Get CRC32 for file:**

```C++
uint32_t crc;

CRC_t<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

int res = ucrc.get_crc(crc, "std_file_to_test_crc");

if( res == 0 )
    //uses crc
```


**Note: methods for calculate CRC file**

>  ```C++
>  int  get_crc(CRC_Type &crc, const char* file_name) const;
>  ```
>  These method are reentrant. He use a buffer on the stack.
>  The buffer size is 4 Kib (4096 bytes) which is optimal for most   systems.
>  If you have a buffer or needs aligned buffer, you can use the following method:
>  
>  ```C++
>  int get_crc(CRC_Type &crc, const char* file_name, void* buf, size_t size_buf) const;
>  ```


**Get CRC32 for single buf:**

```C++
char buf[len_of_buf]; //bla bla

uint32_t crc;

CRC_t<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

crc = ucrc.get_crc(buf, len_of_buf);
//uses crc
```


**Get CRC-ModBus for single buf:**

```C++
char buf[len_of_buf]; //bla bla

uint16_t crc;

CRC_t<16, 0x8005, 0xffff, true, true, 0x0> ucrc;

crc = ucrc.get_crc(buf, len_of_buf);
//uses crc
```



**Get CRC-8 for buf(s) (chunks):**

**Note:**
>  when the method is used `CRC_Type get_raw_crc(CRC_Type crc, const char* buf, size_t len)`
>  for the first byte (or chunk of data) **crc** param must be obtained through a method `get_crc_init()`
>  and in the end you need to call the method: `get_end_crc()`:

```C++
char buf[len_of_buf];   //bla bla
char buf2[len_of_buf2]; //bla bla

uint8_t crc;

CRC_t<8, 0x7, 0x0, false, false, 0x0>  ucrc;

crc = ucrc.get_crc_init();
crc = ucrc.get_raw_crc(buf,  len_of_buf,  crc);  //first chunk
crc = ucrc.get_raw_crc(buf2, len_of_buf2, crc);  //second chunk
crc = ucrc.get_end_crc(crc);
//uses crc
```

**Note: type for CRC**
> You can set the type for CRC yourself (uint8_t, uint16_t, uint32_t, uint64_t), or get through template parameters (correctly):

```C++
char buf[len_of_buf];   //bla bla
char buf2[len_of_buf2]; //bla bla

CRC_t<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>::CRC_Type crc;
CRC_t<32, 0x04C11DB7, 0xFFFFFFFF, true, true, 0xFFFFFFFF>  ucrc;

crc = ucrc.get_raw_crc(buf,  len_of_buf);        //first chunk (Since from version 2.0)
crc = ucrc.get_raw_crc(buf2, len_of_buf2, crc);  //second chunk
crc = ucrc.get_end_crc(crc);
//uses crc
```


More details can be found in the test application: **[crc_test.cpp](./tests/crc_test.cpp)**




## License

[BSD-3-Clause](./LICENSE).
