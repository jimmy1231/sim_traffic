//
// Created by jimmy on 2020-11-30.
//

#include <cstdio>
#include <iostream>
#include <tuple>
#include "dbitmap.h"
#include "rgb.h"
#include "prog.h"

int dbitmap::mark() {
    auto it = dbit_cache.begin();
    for (int i = 0; it != dbit_cache.end(); ++it, ++i) {
        if ((*it).empty()) {
            return i;
        }
    }

    dbit_cache.emplace_back(gridmap());
    int id = (int)dbit_cache.size() - 1;
    return id;
}

void dbitmap::reset(int id) {
    if (id < dbit_cache.size()) {
        gridmap &map = dbit_cache[id];

        for (auto &it : map) {
            std::string key = it.first;
            rgb color = it.second;

            int pos = key.find('-');
            size_t row = std::stoi(key.substr(0, pos));
            size_t col = std::stoi(key.substr(pos+1));

            coords_t coords(row, col);
            set(color, coords);
        }

        map.clear();
    }
}

dbitmap::~dbitmap() {
    if (!dbit_cache.empty()) {
        dbit_cache.clear();
    }
}

void dbitmap::save(int id, rgb &color, const coords_t &coords) {
    if (id < dbit_cache.size()) {
        gridmap &cache = dbit_cache[id];

        size_t row = coords.row;
        size_t col = coords.col;
        std::string key = std::to_string(row) + "-" + std::to_string(col);

        cache[key] = color;
    }
}
