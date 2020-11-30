//
// Created by jimmy on 2020-11-30.
//

#ifndef SIM_TRAFFIC_BB_H
#define SIM_TRAFFIC_BB_H


#include <cstddef>

// bounding box
class bb {
public:
    size_t row_ul, col_ul, row_br, col_br;
    void print() const;
    size_t height() const;
    size_t width() const;
};


#endif //SIM_TRAFFIC_BB_H
