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
#include <ga/union.h>

using namespace ga;

std::vector<std::vector<int>> pixana::blobs(uint8_t threshold)
{

    // First create data structure to store bulk pixels.
    uint16_t w = image_->width(), h = image_->height();
    int len = w * h;
    uint8_t pixels[len];
    union_t<uint8_t> id;

    // Pass 1: Loop through pixels.
    int index = 0;
    uint8_t *pimg = image_->data(), *ppix = pixels;
    for (uint16_t y = 0; y < h; y++)
        for (uint16_t x = 0; x < w; x++)
        {
            // Default is white...
            *ppix = 0;
            if (is_black(pimg, threshold))
            {
                // Get left top, top, right top and left values
                uint8_t
                    lt = y && x ? *(ppix - w - 1) : 0,
                    t = y ? *(ppix - w) : 0,
                    rt = y && (x < w) ? *(ppix - w + 1) : 0,
                    l = x ? *(ppix - 1) : 0;
                // Set the value!
                if (lt)
                    *ppix = lt;
                else if (t)
                    *ppix = t;
                else if (rt)
                    *ppix = rt;
                else if (l)
                    *ppix = l;
                else
                    *ppix = ++index;
                // And create equiv, if any detected.
                uint8_t c = *ppix;
                if (c != t && t)
                    id.merge(c, t); // Top check.
                if (c != rt && rt)
                    id.merge(c, rt); // Right top check.
                if (c != l && l)
                    id.merge(c, l); // Left check.
            }
            pimg++;
            ppix++;
        }

    // Pass 2: Resolve identities and generate the result.
    ppix = pixels;
    uint8_t c, root;
    std::map<uint8_t,std::vector<int>> group;
    while (len--)
    {
        // Is there a pixel?
        if (c = *ppix) {
            if ((root = id.find(c)) != c && root)
                *ppix = root;
            // Add offset to map.
            group[*ppix].push_back(ppix-pixels);
        }
        ppix++;
    }

    // Finally, restructure the result.
    std::vector<std::vector<int>> result;
    for (auto& kv : group) {
        result.push_back(kv.second);
    }
    return result;

}