#pragma once
#include <string>
#ifdef _WIN32
#include <windows.h>
#endif

#ifdef _WIN32
using coding_t = UINT;
#else
using coding_t = const char*;
#endif

namespace turtle {

    class cutf8_converter {

    public:
        enum class coding_opt {
            UTF8 = 0,
            ANSI = 1,
            GBK  = 2
        };

        static constexpr coding_t get_coding(coding_opt c);

        /*
         * USAGE: utf8_to_ansi(str,cutf8_converter::coding::ansi,cutf8_converter::coding::utf8)
         */
        static std::string coding_convert(const std::string& ss, coding_t src_coding, coding_t dst_coding);
    };
}