//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_DBITMAP_H
#define SIM_TRAFFIC_DBITMAP_H

#include "bitmap.h"
#include "world.h"
#include <unordered_map>

class dbitmap : bitmap {
    std::unordered_map<std::string, rgb> map;
    void track_pixel(rgb &color, const coords_t &coords);
public:
    dbitmap(unsigned char *b, size_t h, size_t w) : bitmap(b, h, w) { }
    explicit dbitmap(bitmap &bmp) : bitmap(bmp.buffer, bmp.height, bmp.width) { }

    bool set_visited(rgb &color, const coords_t &&coords);
    void mark();
    void reset();
};


#endif //SIM_TRAFFIC_DBITMAP_H
