#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>

#define USING_CODING_T        using coding_t = UINT;

#define DECLARE_CODING_SET static const UINT utf8 = CP_UTF8;\
static const UINT ansi = CP_ACP;\
static const UINT gbk = 936;

#else
#include <iconv.h>
#include <cstring>

#define USING_CODING_T        using coding_t = char*;

#define DECLARE_CODING_SET static const char utf8[]{ "utf8" };\
static const char gbk[]{ "gbk" };\
static const char ansi[]{ "gbk" }; // TODO: Fix
#endif

namespace turtle {

    class cutf8_converter {

    public:
        USING_CODING_T;
        struct coding {
            DECLARE_CODING_SET;
        };

        // USAGE: utf8_to_ansi(str,cutf8_converter::coding::ansi,cutf8_converter::coding::utf8)
        std::string coding_convert(const std::string& ss, coding_t src_coding, coding_t dst_coding);
    };
}