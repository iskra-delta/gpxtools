/*
 * img_arr_args.h
 * 
 * Snatch main header file.
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 26.02.2023  tstih
 * 
 */
#ifndef __SNATCH_H__
#define __SNATCH_H__

#include <base/img_arr_args.h>

namespace gpxtools {
    struct snatch_args : img_arr_args {
        snatch_args(cxx_argp::parser &parser) : img_arr_args(parser) {}
    };
}

#endif // __SNATCH_H__