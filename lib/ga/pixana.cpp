/*
 * pixana.cpp
 * 
 * Pix. analysis.
 * 
 * MIT License (see: LICENSE)
 * Copyright (c) 2023  Your Company
 * 
 * 20.03.2023  tstih
 * 
 */
#include <ga/ga.h>

using namespace ga;

void pixana::bulk() {
    
    // First create data structure to store bulk pixels.
    uint16_t w=image_->width(), h=image_->height();
    uint8_t pixels[w*h];

    // Loop through pixels.
    int index=0;
    uint8_t *pimg=image_->data(),*ppix=pixels;
    for(uint16_t y=0;y<h;y++)
        for(uint16_t x=0;x<w;x++)
         {
            // Default is white...
            *ppix=0; 
            if (is_black(pimg)) {
                // if all black, then use index.
                if (y) { // Is there a row above current row.
                    if (x && *(ppix-w-1))
                        *ppix=*(ppix-w-1);
                    else if (x<w && *(ppix-w))
                        *ppix=*(ppix-w);
                    else if (x<w-1 && *(ppix-w+1))
                        *ppix=*(ppix-w+1);
                } 
                if (!*ppix && x && *(ppix-1))
                    *ppix=*(ppix-1);
                if (!*ppix) 
                    *ppix=++index;
            }
            pimg++; ppix++;
        }


    // Test display.
    ppix=pixels;
    for(uint16_t y=0;y<h;y++) {
        for(uint16_t x=0;x<w;x++)
            std::cout<<(int)(*ppix++);
        std::cout<<std::endl;
    }

}