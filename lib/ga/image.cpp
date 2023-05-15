/*
 * ga_image.cpp
 * 
 * Image class.
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 18.03.2023  tstih
 * 
 */
#define STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include <ga/ga.h>

using namespace ga;

image::image(std::string path) {
    int channels;
    data_ = ::stbi_load(
        path.c_str(), 
        &width_, 
        &height_, 
        &channels, 
        1); // This will convert any image to grayscale!

    if (data_ == nullptr)
        throw exception("Unable to read image.");
}

image::image(int width, int height, uint8_t init_color) {    
    int len = width * height;
    data_ = new uint8_t[len];  
    width_=width;
    height_=height;
    std::fill(data_, data_ + len, init_color);
}

image::~image() {
    if (data_ != nullptr) ::stbi_image_free(data_);
}

void image::save(std::string path) {
    // Save the image using stb_image_write library (example)
    int result = ::stbi_write_png(
        path.c_str(), 
        width_, 
        height_, 
        1, 
        data_, 
        width_);
    if (result == 0) {
        throw exception("Failed to save image.");
    }
}

void image::draw_image(int x, int y, const image &img) {
    uint8_t *src=img.data(), *dst=data_+getoffs(x,y);
    // While there are rows.
    int h=img.height(),w;
    while(h--) {
        w=img.width();
        // Copy row.
        while (w--)
            *dst++=*src++;
        // Move to next destination position.
        dst+=(width_-img.width());
    }
}

void image::draw_line(int x0, int y0, int x1, int y1, uint8_t attr) {
    for (const auto& offs : ga::bresenham_line(*this,x0,y0,x1,y1)) {
        auto [x,y] = getxy(offs);
        draw_pixel(x,y,attr);
    }
}

void image::draw_rect(int x0, int y0, int x1, int y1, uint8_t attr) {
    draw_line(x0,y0,x1,y0,attr);
    draw_line(x1,y0,x1,y1,attr);
    draw_line(x1,y1,x0,y1,attr);
    draw_line(x0,y1,x0,y0,attr);
}

void image::draw_pixel(int x, int y, uint8_t attr) {
    data_[getoffs(x,y)]=attr;
}