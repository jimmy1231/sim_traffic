//
// Created by jimmy on 2020-11-30.
//

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <cassert>
#include "bitmap.h"

bitmap *bitmap::make_cpy() const {
    auto *buf = (unsigned char *)malloc(nbytes);
    memcpy(buf, buffer, nbytes);
    return new bitmap(buf, height, width);
}

unsigned char &bitmap::operator[](int index) const {
    return buffer[index];
}

unsigned char &bitmap::operator[](size_t index) const {
    return buffer[index];
}

bitmap::~bitmap() {
    free(buffer);
}

rgb &bitmap::get(const coords_t &coords) {
    size_t pos = (get_row(coords) * width + get_col(coords)) * 3;
    rgb *pixel = (rgb *) &(*this)[pos];
    return (*pixel);
}

void bitmap::set(rgb &color, coords_t &coords) {
    rgb &pixel = get(coords);

    // boundary check
    if ((void *) (&pixel + 1 /* sizeof(rgb) */) > (void *) (buffer + nbytes)) {
        size_t pos = (std::get<0>(coords) * width + std::get<1>(coords)) * 3;
        std::cout << "set &buffer[" << pos << "] = " << &pixel << ", &(coords) - (" << get_row(coords) << "," << get_col(coords) << "). "
                  << &pixel << ". rgb=(" << (int)color.r << "," << (int)color.g << "," << (int)color.b << ")" << std::endl;
        exit(EXIT_FAILURE);
    }
    pixel = color;
}

void bitmap::set(rgb &&color, coords_t &coords) {
    rgb &pixel = get(coords);
    pixel = color;
}

bitmap::bitmap(const bitmap &other) {
    height = other.height;
    width = other.width;
    nbytes = width * height;

    buffer = (unsigned char *)malloc(nbytes);
    memcpy(buffer, other.buffer, nbytes);
}
