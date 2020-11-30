//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_DBITMAP_H
#define SIM_TRAFFIC_DBITMAP_H

#include "bitmap.h"
#include "world.h"

class dbitmap {
    bitmap &bmp;
public:
    dbitmap(bitmap &_bmp) : bmp{_bmp} { }

    smart_coords_t & set_visited();
    void mark();
    void reset();
};


#endif //SIM_TRAFFIC_DBITMAP_H
