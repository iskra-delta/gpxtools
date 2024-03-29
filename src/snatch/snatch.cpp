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

#include <cgen/cgen.h>
#include <snatch/snatch.h>

int main(int argc, char *argv[]) {
    
    // Parse command line arguments.
    cxx_argp::parser parser;
    struct gpxtools::snatch_args args(parser);
    if (!parser.parse(argc, argv)) {
		std::cerr << "Invalid command line arguments.\n";
		return 1;
	}

	cgen::cstream cs(std::cout);

	// Code generator
	cs 	<< cgen::header("snatch.cpp",
						"Snatch main file.",
						"MIT License (see: LICENSE)",
						"Copyright (c) 2023 Tomaz Stih",
						"tstih")
		<< cgen::indent(4) // Indent 8 spaces from now on.
		<< std::endl;
}