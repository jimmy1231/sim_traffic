//
// Created by jimmy on 2020-12-01.
//

#ifndef SIM_TRAFFIC_PROG_H
#define SIM_TRAFFIC_PROG_H

#include <cstdio>
#include <tuple>
#include <memory>
#include "rgb.h"
#include "BB.h"
#include "coords_t.h"

extern rgb CLR_TUNNEL;
extern rgb CLR_STATION;
extern rgb CLR_SPAWN_POINT;
extern rgb CLR_PLATFORM;
extern rgb CLR_WHITE;
extern rgb CLR_BLACK;
extern rgb CLR_DVISITED;
extern rgb CLR_DCURRENT;

#define MAX(s1, s2) (s1) > (s2) ? (s1) : (s2)
#define MIN(s1, s2) (s1) < (s2) ? (s1) : (s2)

class entity;
class tunnel;
class platform;
class spawn;
class station;

// comment to enable assert
#define NDEBUG

enum rgb_enum {
    TUNNEL,
    STATION,
    SPAWN_POINT,
    PLATFORM,

    NONE
};

namespace sim {
    inline coords_t relativize(BB &box, coords_t coords){
        return {
            MAX(coords.row - box.row_ul, 0),
            MAX(coords.col - box.col_ul, 0)
        };
    }

    // inverse of relativize
    inline coords_t absolute(BB &box, coords_t coords) {
        return {
            MIN(coords.row + box.row_ul, box.height()),
            MIN(coords.col + box.col_ul, box.width())
        };
    }

    // upper exclusive: lower <= val < upper
    inline bool in_bounds(size_t val, size_t lower, size_t upper){
        return val >= lower && val < upper;
    }

    rgb_enum enumerate(rgb &color);
}

#endif //SIM_TRAFFIC_PROG_H
