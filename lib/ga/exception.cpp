/*
 * ga_exception.cpp
 * 
 * Gpx algorithms implementation.
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 19.03.2023  tstih
 * 
 */
#include <ga/ga.h>

using namespace ga;

const char* exception::what() const noexcept {
    return message_.c_str();
}