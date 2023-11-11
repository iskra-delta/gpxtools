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
#include <map>
#include <tuple>

#include <stb/stb_image.h>
#include <stb/stb_image_write.h>

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
        image(int width, int height, uint8_t init_color = 0);
        virtual ~image();

        inline int width() const { return width_; }
        inline int height() const { return height_; }
        inline uint8_t* data() const { return data_; }
        
        inline std::tuple<int,int> getxy(int offs) const {
            // Assume 1 byte per pixel.
            return { offs%width_, offs/width_ };
        }
        inline int getoffs(int x, int y) const {
            // Assume 1 byte per pixel.
            return y*width_+x;
        }

        void draw_image(int x, int y, const image &img);
        void draw_line(int x0, int y0, int x1, int y1, uint8_t attr);
        void draw_pixel(int x, int y, uint8_t attr);
        void draw_rect(int x0, int y0, int x1, int y1, uint8_t attr);

        void save(std::string path);

    private:
        uint8_t* data_;
        int width_, height_;
    };

    extern std::vector<int> bresenham_line(const image &img, int x0, int y0, int x1, int y1);
    extern std::vector<std::vector<int>> blobs(const image& img, uint8_t threshold);
    extern std::vector<std::pair<int,int>> vectorize(
        const image &img,           // The image.
        std::vector<int> pixels,    // The stroke.
        uint8_t threshold);
    extern uint8_t is_black(uint8_t *pval, uint8_t threshold=32);

} // namespace ga

#endif // __GA_H__