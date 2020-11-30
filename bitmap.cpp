//
// Created by jimmy on 2020-11-30.
//

#include <cstdlib>
#include <cstring>
#include "bitmap.h"

bitmap *bitmap::make_cpy() const {
    size_t nbytes = width *height;
    auto *buf = (unsigned char *)malloc(nbytes);
    memcpy(buf, buffer, nbytes);
    return new bitmap(buf, height, width);
}

unsigned char &bitmap::operator[](int index) {
    return buffer[index];
}

unsigned char &bitmap::operator[](size_t index) {
    return buffer[index];
}

bitmap::~bitmap() {
    free(buffer);
}

rgb &bitmap::get(const coords_t &coords) {
    size_t pos = (std::get<0>(coords) * width + std::get<1>(col)) * 3;
    rgb *pixel = (rgb *) &(*this)[pos];
    return (*pixel);
}

void bitmap::set(rgb color, size_t row, size_t col) {
    rgb pixel = get(row, col);
    pixel = color;
}
