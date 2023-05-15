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

    // Source image.
    ga::image src=ga::image(args.input);
    // Convert to blobs.
    auto result=ga::blobs(src, 32);
    // Final image with space for borders...
    ga::image final(
        (src.width() + 1) * 7 + 1,
        (src.height() + 1) * 3 + 1,
        0xff);
    // Iterate through N vector.
    int i=0;
    for (const auto& inner : result) {
        // Create empty image.
        ga::image dst(src.width(),src.height(),0xff);
        for (const auto& element : inner) 
            (dst.data())[element]=0; // Black.
        int y=i/7, x=i%7;
        final.draw_image(x*(src.width()+1) + 1,y*(src.height()+1) + 1,dst);
        final.draw_rect(
            x * (src.width()+1),
            y * (src.height()+1),
            (x+1) * (src.width()+1),
            (y+1) * (src.height()+1),
            192);
        i++;
    }
    // Draw border areound final.
    final.save(args.output);
}