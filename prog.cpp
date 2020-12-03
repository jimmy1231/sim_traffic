//
// Created by jimmy on 2020-12-03.
//

#include "prog.h"

rgb_enum sim::enumerate(rgb &color) {
    if (color == CLR_TUNNEL) {
        return rgb_enum::TUNNEL;
    }

    if (color == CLR_STATION) {
        return rgb_enum::STATION;
    }

    if (color == CLR_SPAWN_POINT) {
        return rgb_enum::SPAWN_POINT;
    }

    if (color == CLR_PLATFORM) {
        return rgb_enum::PLATFORM;
    }

    return rgb_enum::NONE;
}
