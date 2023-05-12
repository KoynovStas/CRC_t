# Change Log


[**CRC_t**](https://github.com/KoynovStas/CRC_t) - is C++ template for calculation CRC any sizes(width) 1-64 bits.

License: BSD 3-Clause

Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru



---
## [v2.1](https://github.com/KoynovStas/CRC_t/tree/v2.1) (2023-05-12)
[Full Changelog](https://github.com/KoynovStas/CRC_t/compare/v2.0...v2.1)


### New
 - New: use cmake for build tests
 - Fix: use `__INCLUDE_LEVEL__` in `STATIC_ASSERT` for fix ODR in headers


### Refactoring
 - replaced `std::string` to `const char*` in Proxy
 - use `stest_printf` for embedded (was be `std::cerr`)
 - deleted `get_cnt_impl()`, add const `CNT_IMPL`
 - deleted `sstream`, use `TEST_ASSERTF` with `printf`
 - add `static` prefix for some methods


### Tests
 - add to CRC list `CRC-64/MS`
 - add to CRC list `CRC-64/REDIS`
 - add to CRC list `CRC-32/MEF`
 - add to CRC list `CRC-16/M17`
 - add to CRC list `CRC-8/HITAG`




## [v2.0](https://github.com/KoynovStas/CRC_t/tree/v2.0) (2020-05-01)
[Full Changelog](https://github.com/KoynovStas/CRC_t/compare/v1.2...v2.0)


### New
- New: Started using pattern [CRTP](https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern) this allows the use of static polymorphism. And this allows you to extract each algorithm to a separate class!
- New: extracted base class `CRCBase_t` from `CRC_t`
- New: add template parameter `Impl` (Implementation of algorithm)
- New: add implementation of algorithm **CRCImplTable4** - table for half byte (16 elements)
- New: add implementation of algorithm **CRCImplBits** - loop for 8 bits in byte (no table)

- The current version are supported:
   * **CRCImplBits** - loop for 8 bits in byte (no table) - **new**
   * **CRCImplTable4** - table for half byte (16 elements) - **new**
   * **CRCImplTable8** - std table for byte (256 elements)


### Refactoring
- Ref: join `init_xxx_crc_table` to one method (small code)
- Ref: moved `get_raw_normal`/`reflect_crc` from `ImplBits` to Base class


### Tests
 - add to tests **CRCImplBits** strategy
 - add to tests **CRCImplTable4** strategy
 - add `test_crc_impl_1byte`
 - add `test_crc_impl_data_xyz_256`
 - add `test_crc_impl_data_xxx_256`
 - add `test_crc_for_cunks2` for test wrapper `get_raw_crc`
 - add `test_crc_speed` - benchmark for calc speed for 1GB data




## [v1.2](https://github.com/KoynovStas/CRC_t/tree/v1.2) (2018-01-11)
[Full Changelog](https://github.com/KoynovStas/CRC_t/compare/v1.1...v1.2)



### New
- deleted `name` field - user self can add it (if need)


### BugFix
 - BugFix: bad error message if test is fail (`ss` was be on stack)


### Refactoring
 - `reflect` method
 - use `std::ifstream` for calculate crc for file
 - delete prefix `register` - old style
 - moved var `shift` to `get_raw_crc()` method
 - moved calculate `crc_mask` and `top_bit` to methods
 - divided the `init_crc_table` function into **two** functions `normal\reflected`
 - rename `get_final_crc` -> `get_end_crc`


### Tests
 - add to CRC list `CRC-8/BLUETOOTH`
 - add to CRC list `CRC-8/NRSC-5`
 - add to CRC list `CRC-16/NRSC-5`
 - add to CRC list `CRC-17/CAN-FD`
 - add to CRC list `CRC-21/CAN-FD`
 - add to CRC list `CRC-24/OS-9`




## [v1.1](https://github.com/KoynovStas/CRC_t/tree/v1.1) (2017-05-03)
[Full Changelog](https://github.com/KoynovStas/CRC_t/compare/v1.0...v1.1)


### Added
- add method `get_check` - crc for ASCII string '123456789'


### Refactoring
 - Replacement `(const char *)` to `(const void *)` - for ease use methods: `get_crc` and `get_raw_crc`
 - Add `CRC_STATIC_ASSERT` for `Bits` param of template


### Tests
 - add to CRC list `CRC-64/GO-ISO`
 - add to CRC list `CRC-32/AUTOSAR`
 - add to CRC list `CRC-30/CDMA`
 - add to CRC list `CRC-24/LTE-B`
 - add to CRC list `CRC-24/LTE-A`
 - add to CRC list `CRC-24/INTERLAKEN`
 - add to CRC list `CRC-24/BLE`
 - add to CRC list `CRC-16/PROFIBUS`
 - add to CRC list `CRC-16/OPENSAFETY-B`
 - add to CRC list `CRC-16/OPENSAFETY-A`
 - add to CRC list `CRC-16/LJ1200`
 - add to CRC list `CRC-16/GSM`
 - add to CRC list `CRC-16/CMS`
 - add to CRC list `CRC-14/GSM`
 - add to CRC list `CRC-12/GSM`
 - add to CRC list `CRC-11/UMTS`
 - add to CRC list `CRC-10/GSM`
 - add to CRC list `CRC-8/SAE-J1850`
 - add to CRC list `CRC-8/OPENSAFETY`
 - add to CRC list `CRC-8/LTE`
 - add to CRC list `CRC-8/GSM-B`
 - add to CRC list `CRC-8/GSM-A`
 - add to CRC list `CRC-8/AUTOSAR`
 - add to CRC list `CRC-7/UMTS`
 - add to CRC list `CRC-6/GSM`
 - add to CRC list `CRC-4/INTERLAKEN`
 - add to CRC list `CRC-3/GSM`


## [v1.0](https://github.com/KoynovStas/CRC_t/tree/v1.0) (2016-03-03)
