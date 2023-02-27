/*
 * img_args.h
 * 
 * Standard image arguments:
 *  - margin
 *  - input file
 *  - output file
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 27.02.2023  tstih
 * 
 */
#ifndef __IMG_ARGS_H__
#define __IMG_ARGS_H__

#include <cstdint>
#include <string>
#include <vector>

#include <cxx_argp/cxx_argp_parser.h>

namespace gpxtools {
    enum result { SUCCESS = 0, INVALID_ARGS };
    // Standard image arguments.
    struct img_args {
        bool test; // Is test run?
        std::string input; // Input file.
        std::string output; // Output file.
        std::vector<uint16_t> margins; // Image margins.
        inline img_args(cxx_argp::parser &parser) {
            // First set defaults
            test=false;
            input="";
            output="";
            // Add options to parser.
            parser.add_option({"test", 't', nullptr, 0, "Test mode."}, test);
            parser.add_option({"input", 'i', "input-file", 0, "Input file."}, input);
            parser.add_option({"output", 'o', "output-file", 0, "Output file."}, output);
            parser.add_option({"margins", 'm', "margins", 0, "left, top, right, bottom"}, margins);
        }
    };
}

#endif // __IMG_ARGS_H__
