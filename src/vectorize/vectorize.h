/*
 * vectorize.h
 * 
 * Change image to vectors (header).
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 19.03.2023  tstih
 * 
 */
#ifndef __VECTORIZE_H__
#define __VECTORIZE_H__

#include <base/img_arr_args.h>

namespace gpxtools {

    struct vectorize_args : img_args {
        vectorize_args(cxx_argp::parser &parser) : img_args(parser) {}
    };

    
}

#endif // __VECTORIZE_H__