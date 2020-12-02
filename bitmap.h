//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_BITMAP_H
#define SIM_TRAFFIC_BITMAP_H


#include <cstddef>
#include <cstring>
#include "prog.h"
#include "rgb.h"

class bitmap {
public:
    unsigned char *buffer;
    size_t height;
    size_t width;
    size_t nbytes;

    ~bitmap();
    bitmap(size_t h, size_t w) :
        buffer{(unsigned char *)malloc(w * h * 3)},
        height{h},
        width{w},
        nbytes{w * h * 3} {
        memset(buffer, CLR_WHITE.r, nbytes);
    }
    bitmap(bitmap &&other)  noexcept :
        buffer{other.buffer},
        height{other.height},
        width{other.width},
        nbytes{other.nbytes} { }
    bitmap(const bitmap &other);
    bitmap(unsigned char *b, size_t h, size_t w)
        : buffer{b}, height{h}, width{w}, nbytes{h * w * 3} { }

    bitmap *make_cpy() const;
    /*
     * Returns a direct reference of an 'rgb' struct in the
     * buffer location of 'row' and 'col'.
     */
    rgb &get(const coords_t &coords);
    void set(rgb &color, coords_t &coords);
    void set(rgb &&color, coords_t &coords);
    unsigned char& operator[](int index) const;
    unsigned char& operator[](size_t index) const;
};


#endif //SIM_TRAFFIC_BITMAP_H
