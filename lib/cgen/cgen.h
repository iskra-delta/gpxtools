/*
 * cgen.h
 *
 * Simple stream based code generator
 * header only C++ library.
 *
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 *
 * 26.02.2023  tstih
 *
 */
#ifndef __CGEN_H__
#define __CGEN_H__

#include <ostream>
#include <iomanip>

namespace cgen
{
    // Custom stream.
    class code_stream : public std::basic_ostream<char>
    {
    public:
        inline code_stream(std::streambuf *buf) : std::basic_ostream<char>(buf) {}

        inline code_stream &write(const char *s, std::streamsize n)
        {
            return *this;
        }

        code_stream& set_tab_size(int n) {
            tab_size_ = n;
            return *this;
        }
    private:
        int tab_size_ = 4; // Default tab size.
    };

    code_stream& tab_size(code_stream& os, int n) {
        os.set_tab_size(n);
        return os;
    }

} // namespace cgen

#endif // __CGEN_H__
