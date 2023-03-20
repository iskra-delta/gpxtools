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
    // Custom stream buffer that tracks rows.
    class cstreambuf : public std::streambuf {
    public:
        cstreambuf(std::streambuf* buf) : buf_(buf) {

        }
        virtual int_type overflow(int_type ch) override {
            if (ch == '\n') {
                // Remember start of row position.
                row_start_ = buf_->pubseekoff(0, std::ios_base::cur);
                // Add indent.
                if (indent_)
                    for(unsigned char i=0;i<indent_;i++)
                        buf_->sputc(' ');
            }
            return buf_->sputc(ch);
        }
    
        // We don't let indent longer than 255...
        void set_indent(unsigned char indent) {
            indent_=indent;
        }
    private:
        unsigned char indent_ {0}; // Default = no indent.
        unsigned char tab_size_ {0};
        std::streambuf* buf_;
        std::streampos row_start_;
    };

    // Custom stream.
    class cstream : public std::basic_ostream<char>
    {
    public:
        cstream(cstreambuf *buf) : std::basic_ostream<char>(buf) {
            buf_=buf;
        }
        cstream& set_indent(unsigned char indent) {
            buf_->set_indent(indent);
            return *this;
        }
    private:
        cstreambuf *buf_;
    };

        // File header.
    class header {
    public:
        header(
            std::string filename,
            std::string desc,
            std::string license,
            std::string copyright,
            std::string author) :
            filename_(filename),
            desc_(desc),
            license_(license),
            copyright_(copyright),
            author_(author)
        {}
        cstream &operator()(cstream &out) const {
            auto t = std::time(nullptr);
            auto tm = *std::localtime(&t);
            out << "/*" << std::endl << " * " << filename_ << std::endl
                << " *" << std::endl << " * " << desc_ << std::endl 
                << " *" << std::endl 
                << " * "  << license_ << std::endl
                << " * " << copyright_ << std::endl
                << " *" << std::endl
                << " * " << std::put_time(&tm, "%d-%m-%Y") << author_ << std::endl
                << " *" << std::endl << " */" << std::endl;
            return out;
        }
    private:
        std::string filename_;
        std::string desc_;
        std::string license_;
        std::string copyright_;
        std::string author_;
    };

    class indent {
    public:
        indent(unsigned char indent) : indent_(indent) {} 
        cstream &operator()(cstream &out) const {
            out.set_indent(indent_);
            return out;
        }
    private:
        unsigned char indent_;
    };

    cstream& operator<<(cstream& out, const indent& indent) {
        return indent(out);
    }

    cstream& operator<<(cstream& out, const header& h) {
        return h(out);
    }

} // namespace cgen

#endif // __CGEN_H__
