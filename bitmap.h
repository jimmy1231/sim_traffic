//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_BITMAP_H
#define SIM_TRAFFIC_BITMAP_H


#include <cstddef>

class bitmap {
public:
    unsigned char *buffer;
    size_t height;
    size_t width;

    ~bitmap();
    bitmap(unsigned char *b, size_t h, size_t w)
        : buffer{b}, height{h}, width{w} { }

    bitmap *make_cpy();
    unsigned char& operator[](int index);
    unsigned char& operator[](size_t index);
};


#endif //SIM_TRAFFIC_BITMAP_H
