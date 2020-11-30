//
// Created by jimmy on 2020-11-30.
//

#include "rgb.h"

bool rgb::operator==(const rgb &other) const {
    return r == other.r && g == other.g && b == other.b;
}

rgb &rgb::operator=(const rgb &other) {
    r = other.r;
    g = other.g;
    b = other.b;
}
