//
// Created by jimmy on 2020-12-01.
//

#ifndef SIM_TRAFFIC_PROG_H
#define SIM_TRAFFIC_PROG_H

#include <cstdio>
#include <tuple>
#include <memory>
#include "rgb.h"

extern rgb CLR_TUNNEL;
extern rgb CLR_WHITE;
extern rgb CLR_BLACK;
extern rgb CLR_DISCOVERY_VISITED;

typedef std::tuple<size_t, size_t> coords_t;
typedef std::shared_ptr<coords_t> smart_coords_t;

#define NULL_COORD coords_t(-1, -1)
#define POS(row, col, w, h) ((row)*(w) + (col))*3
#define SET_VISITED(frame, i) frame[i] = 112; \
	frame[i+1] = 16; \
	frame[i+2] = 81
#define MATCH(frame,i,r,g,b) frame[i] == (r) && frame[i+1] == (g) && frame[i+2] == (b)

#define MAX(s1, s2) (s1) > (s2) ? (s1) : (s2)
#define MIN(s1, s2) (s1) < (s2) ? (s1) : (s2)

inline coords_t get_coords(size_t row, size_t col) {
    return std::make_tuple(row, col);
}

inline size_t get_row(coords_t &coords) {
    return std::get<0>(coords);
}

inline size_t get_col(coords_t &coords) {
    return std::get<1>(coords);
}

inline size_t get_row(const coords_t &coords) {
    return std::get<0>(coords);
}

inline size_t get_col(const coords_t &coords) {
    return std::get<1>(coords);
}

#endif //SIM_TRAFFIC_PROG_H
