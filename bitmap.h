//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_BITMAP_H
#define SIM_TRAFFIC_BITMAP_H


#include <cstddef>
#include "prog.h"
#include "rgb.h"

class bitmap {
public:
    unsigned char *buffer;
    size_t height;
    size_t width;

    ~bitmap();
    bitmap(bitmap &&other)  noexcept :
        buffer{other.buffer},
        height{other.height},
        width{other.width} { };
    bitmap(const bitmap &other);
    bitmap(unsigned char *b, size_t h, size_t w)
        : buffer{b}, height{h}, width{w} { }

    bitmap *make_cpy() const;
    /*
     * Returns a direct reference of an 'rgb' struct in the
     * buffer location of 'row' and 'col'.
     */
    rgb &get(const coords_t &coords);
    void set(rgb &color, coords_t &coords);
    unsigned char& operator[](int index);
    unsigned char& operator[](size_t index);
};


#endif //SIM_TRAFFIC_BITMAP_H
