//
// Created by jimmy on 2020-11-30.
//

#include <cstdio>
#include <tuple>
#include <memory>
#include "dbitmap.h"
#include "rgb.h"
#include "world.h"

bool dbitmap::set_visited(rgb &color, const coords_t &&coords) {
    rgb pixel = this->get(coords);
    if (pixel == color) {
        track_pixel(pixel, coords);
        return true;
    }

    return false;
}

void dbitmap::mark() {
    reset();
}

void dbitmap::reset() {
    for (auto &it : map) {
        std::string key = it.first;
        rgb color = it.second;

        int pos = key.find('-');
        size_t row = std::stoi(key.substr(0, pos));
        size_t col = std::stoi(key.substr(pos+1));
        set(color, row, col);
    }

    map.clear();
}

void dbitmap::track_pixel(rgb &color, const coords_t &coords) {
    size_t row = std::get<0>(coords);
    size_t col = std::get<1>(coords);
    std::string key = std::to_string(row) + "-" + std::to_string(col);
    map.insert(std::make_pair(key, color));
}
