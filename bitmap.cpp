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
    size_t pos = (std::get<0>(coords) * width + std::get<1>(coords)) * 3;
    rgb *pixel = (rgb *) &(*this)[pos];
    return (*pixel);
}

void bitmap::set(rgb &color, coords_t &coords) {
    rgb &pixel = get(coords);
    pixel = color;
}

bitmap::bitmap(const bitmap &other) {
    height = other.height;
    width = other.width;

    size_t nbytes = width * height;
    buffer = (unsigned char *)malloc(nbytes);
    memcpy(buffer, other.buffer, nbytes);
}