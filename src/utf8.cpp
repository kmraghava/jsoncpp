
#include <cstdint>
#include "utf8.hpp"

bool utf8::check_string (std::string_view str, long len)
{
    long  i = 0,
          check_length = str.length();

    if (len > 0 && len < check_length)
        check_length = len;

    while (i < check_length)
    {
        uint8_t   c = static_cast<uint8_t>(str[i]);
        size_t    bytes_to_check = 0;
        uint32_t  codepoint = 0;

        // 1. First-Byte Fast Intercept
        if (c <= 0x7F)
        {
            bytes_to_check = 1;
            codepoint = c;
        }
        // 0xC0 and 0xC1 are hard-banned (Guaranteed overlongs)
        else if (c >= 0xC2 && c <= 0xDF)
        {
            bytes_to_check = 2;
            codepoint = c & 0x1F;
        } 
        else if (c >= 0xE0 && c <= 0xEF)
        {
            bytes_to_check = 3;
            codepoint = c & 0x0F;
        }
        // 0xF5 and above are hard-banned (Out of Unicode bounds)
        else if (c >= 0xF0 && c <= 0xF4)
        {
            bytes_to_check = 4;
            codepoint = c & 0x07;
        }
        else
        {
            // Catches 0xC0, 0xC1, >= 0xF5, and stray continuation bytes
            return false;
        }

        // 2. Prevent out-of-bounds string reading
        if (i + bytes_to_check > str.length())
            return false; 

        // 3. Process continuation bytes
        for (size_t j = 1; j < bytes_to_check; ++j)
        {
            uint8_t next_byte = static_cast<uint8_t>(str[i + j]);

            if ((next_byte & 0xC0) != 0x80)
                return false; 

            codepoint = (codepoint << 6) | (next_byte & 0x3F);
        }

        // 4. Strict Code Point Validation Checks
        // Overlong edge-cases for 3 and 4 byte lengths
        if (bytes_to_check == 3 && codepoint < 0x800  ) return false;
        if (bytes_to_check == 4 && codepoint < 0x10000) return false;

        // Reject UTF-16 Surrogates
        if (codepoint >= 0xD800 && codepoint <= 0xDFFF) return false;

        // Reject values past the maximum Unicode limit 
        // (Catches edge cases within the 0xF4 block, like 0xF4 0x90 0x80 0x80 which is U+110000)
        if (codepoint > 0x10FFFF) return false;

        i += bytes_to_check;
    }

    return true;
}
