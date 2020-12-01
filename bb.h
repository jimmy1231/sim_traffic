//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_BB_H
#define SIM_TRAFFIC_BB_H


#include <cstddef>
#include "prog.h"
#include "world.h"

// bounding box, all bounds are inclusive
class bb {
public:
    size_t row_ul, col_ul, row_br, col_br;

    bb(bb &other) = default;
    bb(bb &&other)  noexcept :
        row_ul{other.row_ul},
        col_ul{other.col_ul},
        row_br{other.row_br},
        col_br{other.col_br} { };
    bb(size_t rul, size_t cul, size_t rbr, size_t cbr) :
        row_ul{rul},
        col_ul{cul},
        row_br{rbr},
        col_br{cbr} { };

    void print() const;
    coords_t top_left() const;
    coords_t bot_right() const;
    size_t height() const;
    size_t width() const;

    bb &operator=(const bb &other);
};


#endif //SIM_TRAFFIC_BB_H
