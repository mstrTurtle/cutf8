#pragma once
#include <string>

#ifdef _WIN32
#include <windows.h>

#else
#include <iconv.h>
#include <cstring>

#endif

namespace turtle {

    class cutf8_converter {

    public:
#ifdef _WIN32
        static const UINT utf8 = CP_UTF8;
        static const UINT ansi = CP_ACP;
        static const UINT gbk = 936;
#else
        static const char utf8[]{ "utf8" };
        static const char gbk[]{ "gbk" };
        static const char ansi[]{ "gbk" }; // TODO: Fix

#endif

#ifdef _WIN32

// Usage: utf8_to_ansi(std::string{"ÄãºÃ"},"CP_UTF8","CP_ACP");
        std::string coding_convert(const std::string& ss, UINT src_coding, UINT dst_coding)
        {
            const char* src_str = ss.c_str();
            int len = ss.length();
            wchar_t* temp = new wchar_t[len + 1];
            MultiByteToWideChar(src_coding, 0, src_str, -1, temp, len);

            int len_dst = len * 2 + 2;
            char* ans = new char[len_dst + 1];
            WideCharToMultiByte(dst_coding, 0, temp, -1, ans, len_dst, NULL, NULL);

            delete[] temp;
            return std::string{ std::move(ans) };
        }
#else


// Usage: ansi_to_utf8(std::string{"ÄãºÃ"},"gbk","utf8");
        std::string coding_convert(const std::string& ss, char* src_coding, char* dst_coding)
        {
            char* src = ss.c_str();
            size_t len_src = ss.length();
            size_t len_dst
                if (!strcmp(src_coding, "utf8"))
                    len_dst = len_src * 2 + 2;
                else
                    len_dst = len_src + 1;
            char* dst = new char[len_dst];
            iconv_t conv = iconv_open(dst_coding, src_coding);

            if (!conv) throw "open iconv error";

            if (iconv(conv, &src, &len_src, &dst, &len_dst) == -1) throw "convert error";

            iconv_close(conv);

            return std::string{ std::move{dst} };
        }


#endif
    };
}