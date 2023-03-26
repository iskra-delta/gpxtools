/*
 * vectorize.cpp
 * 
 * Change image to vectors.
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 19.03.2023  tstih
 * 
 */

#include <iostream>
#include <memory>

#include <cxx_argp/cxx_argp_parser.h>

#include <cgen/cgen.h>
#include <vectorize/vectorize.h>

#include <ga/ga.h>

int main(int argc, char *argv[]) {
    
    // Parse command line arguments.
    cxx_argp::parser parser;
    struct gpxtools::vectorize_args args(parser);
    if (!parser.parse(argc, argv)) {
		std::cerr << "Invalid command line arguments.\n";
		return 1; 
	}

    auto img=std::make_unique<ga::image>(args.input);
    auto pixana=ga::pixana(img.get());
    auto result=pixana.blobs();
    
}
