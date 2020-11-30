//
// Created by jimmy on 2020-11-30.
//

#include <cstdlib>
#include <string.h>
#include "bitmap.h"

bitmap *bitmap::make_cpy() {
    size_t nbytes = width *height;
    auto *buf = (unsigned char *)malloc(nbytes);
    memcpy(buf, buffer, nbytes);
    return new bitmap(buf, height, width);
}

unsigned char& bitmap::operator[](int index) {
    return buffer[index];
}

unsigned char &bitmap::operator[](size_t index) {
    return buffer[index];
}

bitmap::~bitmap() {
    free(buffer);
}
