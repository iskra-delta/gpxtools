/*
 * snatch.cpp
 * 
 * Snatch main file.
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 26.02.2023  tstih
 * 
 */
#include <iostream>

#include <cxx_argp/cxx_argp_parser.h>

#include <snatch/snatch.h>

int main(int argc, char *argv[]) {
    
    // Parse command line arguments.
    cxx_argp::parser parser;
    struct snatch::args args = { false };
    parser.add_option({"test", 't', nullptr, 0, "test"}, args.test);
    if (parser.parse(argc, argv)) {
		std::cerr << "parsing OK\n";
	} else {
		std::cerr << "there was an error - exiting\n";
		return 1;
	}

    
}