//
// Created by jimmy on 2020-12-05.
//

#include "coords_t.h"

bool coords_t::operator<(const coords_t &other) const {
    return (row < other.row) || (row == other.row && col < other.col);
}

bool coords_t::operator<(coords_t &&other) const {
    return (row < other.row) || (row == other.row && col < other.col);
}

bool coords_t::operator<=(const coords_t &other) const {
    return (row < other.row) || (row == other.row && col <= other.col);
}

bool coords_t::operator<=(coords_t &&other) const {
    return (row < other.row) || (row == other.row && col <= other.col);
}

bool coords_t::operator>(const coords_t &other) const {
    return (row > other.row) || (row == other.row && col > other.col);
}

bool coords_t::operator>(coords_t &&other) const {
    return (row > other.row) || (row == other.row && col > other.col);
}

bool coords_t::operator>=(const coords_t &other) const {
    return (row > other.row) || (row == other.row && col >= other.col);
}

bool coords_t::operator>=(coords_t &&other) const {
    return (row > other.row) || (row == other.row && col >= other.col);
}
