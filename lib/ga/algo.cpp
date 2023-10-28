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

#include <vector>
#include <set>

namespace ga
{

    std::vector<int> bresenham_line(
        const image &img,       // Image.
        int x0, int y0, int x1, int y1)
    {
        std::vector<int> result;

        // calculate differences between endpoints
        int dx = abs(x1 - x0);
        int dy = abs(y1 - y0);

        // determine sign for increments
        int sx = (x0 < x1) ? 1 : -1;
        int sy = (y0 < y1) ? 1 : -1;

        // initialize error term
        int err = dx - dy;

        // set starting point
        int x = x0;
        int y = y0;

        while (true)
        {
            // add index of current point to line_indices
            int index = y * img.width() + x;

            result.push_back(index);

            // check if end of line has been reached
            if (x == x1 && y == y1)
            {
                break;
            }

            // calculate error term and move to next pixel
            int e2 = 2 * err;
            if (e2 > -dy)
            {
                err -= dy;
                x += sx;
            }
            if (e2 < dx)
            {
                err += dx;
                y += sy;
            }

            // check if current pixel is outside image bounds
            if (x < 0 || x >= img.width() || y < 0 || y >= img.height())
                break;
        }

        // If we're here, it's a line!
        return result;
    }

    std::vector<std::vector<int>> blobs(const image &img, uint8_t threshold)
    {
        // First create data structure to store bulk pixels.
        uint16_t w = img.width(), h = img.height();
        int len = w * h;
        uint8_t pixels[len];
        union_t<uint8_t> id;

        // Pass 1: Loop through pixels.
        int index = 0;
        uint8_t *pimg = img.data(), *ppix = pixels;
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
        std::map<uint8_t, std::vector<int>> group;
        while (len--)
        {
            // Is there a pixel?
            if (c = *ppix)
            {
                if ((root = id.find(c)) != c && root)
                    *ppix = root;
                // Add offset to map.
                group[*ppix].push_back(ppix - pixels);
            }
            ppix++;
        }

        // Finally, restructure the result.
        std::vector<std::vector<int>> result;
        for (auto &kv : group)
        {
            result.push_back(kv.second);
        }
        return result;
    }

    void move_elem(std::set<int> sfrom, std::set<int> sto, int pt) {
        sto.insert(sfrom.extract(pt).value());
    }

    void move_elem(std::set<int> sfrom, std::set<int> sto, std::set<int> pts) {
        sto.insert(sfrom.extract(pt).value());
    }

    int furthest_point(
        int pt,
        const image &img,           // The image.
        std::set<int> pixels,       // The stroke.
        uint8_t threshold) {

        // Max distance and result index.
        int dist=0, result=pt;

        // Get x and y.
        auto [x0, y0] = img.getxy(pt);
        for (const auto npt : pixels) {
            auto [x1,y1] = img.getxy(npt);
            int ndist=std::max(y1-y0, x1-x0);
            if (ndist > dist) {
                dist=ndist;
                result=npt;
            }
        }

        // Return index.
        return result;
    }

    std::vector<std::pair<int,int>> match_line(
        int pstart,
        int pend,
        const image &img,
        std::set<int> unused 
    ) {
        auto [x0, y0] = 
    }

    std::vector<std::pair<int,int>> vectorize(
        const image &img,           // The image.
        std::vector<int> pixels,    // The stroke.
        uint8_t threshold){         // Black pixel threshold.

        // Result.
        std::vector<std::pair<int,int>> lines;

        // Vector should already be sorted if coming from blobs.
        std::sort(pixels.begin(), pixels.end());

        // Used, unused and visited pixels. Initialize unset to pixels.
        std::set<int> used, visited, unused(pixels.begin(),pixels.end());

        // Get first element.
        auto pstart=*unused.begin();
        while (!unused.empty()) { // While there are any pixels inside.
            auto pend=furthest_point(pstart, img, unused, threshold);
            if (pstart==pend) {
                std::pair<int,int> line={pstart,pend};
                lines.push_back(line);
                move_elem(unused, used, pstart); // unused->used.
            } else {
                // Try to match the line.
                auto line=match_line(pstart,pend, img, unused);
                if (line.empty()) { // No match -> remove end and retry.
                    move_elem(unused, visited, pend);
                } else { // Yuuperoo. A match.
                    // Restore all visited nodes.
                    // Move all matched pixels to used.
                    // Push pixels to result.
                }
            }
        }
        // Return result.
        return lines;
    }


    uint8_t is_black(uint8_t *pval, uint8_t threshold)
    {
        return (*pval) <= threshold;
    }

} // namespace ga