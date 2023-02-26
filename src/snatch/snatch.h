/*
 * snatch.h
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

namespace snatch {
    enum result { SUCCESS = 0, INVALID_ARGS };

    struct args {
        bool test; // Is test run?
    };
}

#endif // __SNATCH_H__