/*
 * ga.h
 * 
 * Gpx algos include file.
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 19.03.2023  tstih
 * 
 */
#ifndef __GA_H__
#define __GA_H__

#include <exception>
#include <string>
#include <climits>
#include <cstdint>
#include <algorithm>
#include <iostream>
#include <vector>

#include <stb/stb_image.h>

namespace ga
{

    // Exception class.
    class exception : public std::exception
    {
    public:
        exception(const std::string &message) : message_(message) {}
        virtual const char* what() const noexcept override;
    private:
        std::string message_;
    };

    // Image class.
    class image {
    public:
        image(std::string path);
        virtual ~image();
        inline int width() const { return width_; }
        inline int height() const { return height_; }
        inline uint8_t* data() const { return data_; }
    private:
        uint8_t* data_;
        int width_, height_;
    };

    // Pix. analysis.
    class pixana
    {
    public:
        pixana(const image *image): image_(image) {}
        void bulk();
    protected:
        inline uint8_t is_black(uint8_t *pval) { return (*pval)<=32; }
    private:
        const image *image_;
    };
} // namespace ga

#endif // __GA_H__