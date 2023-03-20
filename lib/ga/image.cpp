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

image::~image() {
    if (data_ != nullptr) ::stbi_image_free(data_);
}