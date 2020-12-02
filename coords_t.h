//
// Created by jimmy on 2020-12-02.
//

#ifndef SIM_TRAFFIC_COORDS_T_H
#define SIM_TRAFFIC_COORDS_T_H

#include "prog.h"

class coords_t {
public:
    size_t row;
    size_t col;

    coords_t(size_t r, size_t c) : row(r), col(c) { }
    coords_t(const coords_t &other) = default;
    coords_t(coords_t &&other) = default;

    coords_t &operator=(const coords_t &other) = default;
    coords_t &operator=(coords_t &&other) = default;
};


#endif //SIM_TRAFFIC_COORDS_T_H
