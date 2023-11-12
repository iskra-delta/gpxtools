#include <gtest/gtest.h>

#include <ga/ga.h>

TEST(ga_tests,blob) {
    // Source image.
    ga::image src=ga::image("data/test-blob.png");
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
    // Draw border around final.
    final.save("data/test-blob-out.png");
}

TEST(ga_tests,lines) {
    // Source image.
    ga::image src=ga::image("data/gamepad-top.png");
    // Convert to extract blobs.
    auto result=ga::blobs(src, 32);
    // Final image with space for borders...
    ga::image final(
        (src.width() + 1) * 7 + 1,
        (src.height() + 1) * 3 + 1,
        0xff);
    // There should be just one inner blob.
    int i=0;
    for(auto blob:result) {
        auto lines=ga::vectorize(src,blob,32);
        // Create inner image.
        ga::image dst(src.width(),src.height(),0xff);
        for (const auto& line : lines) {
            auto [x0, y0] = src.getxy(line.first);
            auto [x1, y1] = src.getxy(line.second);
            dst.draw_line(x0,y0,x1,y1,0);
        }
        // And append to combined image.
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
    
    // Draw border around final.
    final.save("data/gamepad-out.png");
}