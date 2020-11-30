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