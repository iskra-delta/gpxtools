/*
 * img_arr_args.h
 * 
 * Image array args.
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 27.02.2023  tstih
 * 
 */
#ifndef __IMG_ARR_ARGS_H__
#define __IMG_ARR_ARGS_H__

#include <string>
#include <vector>

#include <base/img_args.h>

namespace gpxtools {
    // Image array arguments.
    struct img_arr_args : img_args {       
        uint16_t glyph_width; // Array member width.
        uint16_t glyph_height; // Array member height.
        std::vector<uint16_t> paddings; // Image padding.
        inline img_arr_args(cxx_argp::parser &parser) : img_args(parser) {
            // Defaults.
            glyph_width=8;
            glyph_height=8;
            // Populate parser.
            parser.add_option({"width", 'w', "glyph-width", 0, "Width of individual glyph"}, glyph_width);
            parser.add_option({"height", 'h', "glyph-height", 0, "Height of individual glyph"}, glyph_height);
        }
    };
}

#endif // __IMG_ARR_ARGS_H__