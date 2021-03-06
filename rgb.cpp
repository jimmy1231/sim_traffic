//
// Created by jimmy on 2020-11-30.
//

#include "rgb.h"
#include <sstream>

bool rgb::operator==(const rgb &other) const {
    return r == other.r && g == other.g && b == other.b;
}

rgb &rgb::operator=(const rgb &other) {
    r = other.r;
    g = other.g;
    b = other.b;

    return (*this);
}

unsigned char rgb::average() const {
    return (unsigned char) ((float)r + (float)g + (float)b / 3);
}

bool rgb::operator!=(const rgb &other) const {
    return !((*this) == other);
}

std::string rgb::str() const {
    std::stringstream sstream;
    sstream << "(" << r << "," << b << "," << g << ")";
    return sstream.str();
}
