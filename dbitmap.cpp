//
// Created by jimmy on 2020-11-30.
//

#include <cstdio>
#include <tuple>
#include <memory>
#include "dbitmap.h"
#include "rgb.h"
#include "prog.h"

bool dbitmap::set_visited(int id, rgb &color, const coords_t &coords) {
    rgb pixel = this->get(coords);
    if (pixel == color) {
        track_pixel(id, pixel, coords);
        return true;
    }

    return false;
}

int dbitmap::mark() {
    auto it = dbit_cache.begin();
    for (int i = 0; it != dbit_cache.end(); ++it, ++i) {
        if ((*it) == nullptr) {
            dbit_cache[i] = new gridmap();
            return i;
        }
    }

    dbit_cache.emplace_back(new gridmap());
    return (int)dbit_cache.size() - 1;
}

void dbitmap::reset(int id) {
    gridmap *map = dbit_cache[id];
    if (map != nullptr) {
        for (auto &it : *map) {
            std::string key = it.first;
            rgb color = it.second;

            int pos = key.find('-');
            size_t row = std::stoi(key.substr(0, pos));
            size_t col = std::stoi(key.substr(pos+1));

            coords_t coords(row, col);
            set(color, coords);
        }

        // free
        delete map;
        dbit_cache[id] = nullptr;
    }
}

void dbitmap::track_pixel(int id, rgb &color, const coords_t &coords) {
    gridmap *cache = dbit_cache[id];
    if (cache != nullptr) {
        size_t row = std::get<0>(coords);
        size_t col = std::get<1>(coords);
        std::string key = std::to_string(row) + "-" + std::to_string(col);
        cache->insert(std::make_pair(key, color));
    }
}

dbitmap::~dbitmap() {
    auto it = dbit_cache.begin();
    for (; it != dbit_cache.end(); ++it) {
        delete (*it);
    }

    dbit_cache.clear();
}
