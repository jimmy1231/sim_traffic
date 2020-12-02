//
// Created by jimmy on 2020-11-30.
//

#include <cstdio>
#include "bb.h"

void bb::print() const {
    printf("UpLeft: (%d, %d); BottomRight: (%d, %d)\n",
           (int)row_ul, (int)col_ul,
           (int)row_br, (int)col_br);
}

size_t bb::height() const {
    return row_br - row_ul;
}

size_t bb::width() const {
    return col_br - col_ul;
}

bb &bb::operator=(const bb &other) {
    row_ul = other.row_ul;
    col_ul = other.col_ul;
    row_br = other.row_br;
    col_br = other.col_br;
    return (*this);
}

coords_t bb::top_left() const {
    return get_coords(row_ul, col_ul);
}

coords_t bb::bot_right() const {
    return get_coords(row_br, col_br);
}

size_t bb::size() const {
    return height() * width();
}
