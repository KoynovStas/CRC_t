# Change Log


[**CRC_t**](https://github.com/KoynovStas/CRC_t) - is C++ template for calculation CRC any sizes(width) 1-64 bits.

License: BSD 3-Clause

Copyright (c) 2015, Koynov Stas - skojnov@yandex.ru



---



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
