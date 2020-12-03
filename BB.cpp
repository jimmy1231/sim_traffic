//
// Created by jimmy on 2020-11-30.
//

#include <cstdio>
#include "BB.h"

void BB::print() const {
    printf("UpLeft: (%d, %d); BottomRight: (%d, %d)\n",
           (int)row_ul, (int)col_ul,
           (int)row_br, (int)col_br);
}

size_t BB::height() const {
    return row_br - row_ul;
}

size_t BB::width() const {
    return col_br - col_ul;
}

BB &BB::operator=(const BB &other) {
    row_ul = other.row_ul;
    col_ul = other.col_ul;
    row_br = other.row_br;
    col_br = other.col_br;
    return (*this);
}

coords_t BB::top_left() const {
    return coords_t(row_ul, col_ul);
}

coords_t BB::bot_right() const {
    return coords_t(row_br, col_br);
}

size_t BB::size() const {
    return height() * width();
}
