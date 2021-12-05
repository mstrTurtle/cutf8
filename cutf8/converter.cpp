#include "converter.h"

namespace turtle {

    std::string cutf8_converter::coding_convert(const std::string& ss, coding_t src_coding, coding_t dst_coding)
    {
#ifdef _WIN32
        const char* src_str = ss.c_str();
        int len = (int) ss.length();
        wchar_t* temp = new wchar_t[len + 1];
        MultiByteToWideChar(src_coding, 0, src_str, -1, temp, len);

        int len_dst = len * 2 + 2;
        char* ans = new char[len_dst + 1];
        WideCharToMultiByte(dst_coding, 0, temp, -1, ans, len_dst, NULL, NULL);

        delete[] temp;
        return std::string{ std::move(ans) };
#else
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
#endif
    }
}