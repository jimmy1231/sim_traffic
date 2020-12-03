//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_BB_H
#define SIM_TRAFFIC_BB_H


#include <cstddef>
#include <iostream>
#include "coords_t.h"

// bounding box, all bounds are exclusive
class BB {
public:
    size_t row_ul, col_ul, row_br, col_br;

    BB(BB &other) = default;
    BB(BB &&other)  noexcept :
        row_ul{other.row_ul},
        col_ul{other.col_ul},
        row_br{other.row_br},
        col_br{other.col_br} { };
    BB(size_t rul, size_t cul, size_t rbr, size_t cbr) :
        row_ul{rul},
        col_ul{cul},
        row_br{rbr},
        col_br{cbr} { };

    void print() const;
    coords_t top_left() const;
    coords_t bot_right() const;
    size_t height() const;
    size_t width() const;
    size_t size() const;

    BB &operator=(const BB &other);
};

#endif //SIM_TRAFFIC_BB_H
