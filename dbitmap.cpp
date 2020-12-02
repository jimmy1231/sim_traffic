//
// Created by jimmy on 2020-11-30.
//

#include <cstdio>
#include <iostream>
#include <tuple>
#include <memory>
#include "dbitmap.h"
#include "rgb.h"
#include "prog.h"

bool dbitmap::set_visited(int id, rgb &color, const coords_t &coords) {
    rgb &pixel = this->get(coords);
    if (pixel == color) {
        track_pixel(id, pixel, coords);

        coords_t cpy = coords;
        set(CLR_DISCOVERY_VISITED, cpy);
        return true;
    }

    return false;
}

int dbitmap::mark() {
    auto it = dbit_cache.begin();
    for (int i = 0; it != dbit_cache.end(); ++it, ++i) {
        if ((*it).empty()) {
            std::cout << "mark: " << i << std::endl;
            return i;
        }
    }

    dbit_cache.emplace_back(gridmap());
    int id = (int)dbit_cache.size() - 1;
    std::cout << "mark: " << id << std::endl;
    return id;
}

void dbitmap::reset(int id) {
    std::cout << "reset: " << id << std::endl;
    if (id < dbit_cache.size()) {
        gridmap &map = dbit_cache[id];

        for (auto &it : map) {
            std::string key = it.first;
            rgb color = it.second;
//            std::cout << "reset map: " << it.first << " -> "
//                << "(" << (int)color.r << "," << (int)color.g << "," << (int)color.b << ")" << std::endl;

            int pos = key.find('-');
            size_t row = std::stoi(key.substr(0, pos));
            size_t col = std::stoi(key.substr(pos+1));

//            std::cout << "color: " << &it.second << " -> " << &color << std::endl;
            coords_t coords(row, col);
            set(color, coords);
        }

//        for (auto &it : map) {
//            std::string key = it.first;
//            rgb color = it.second;
//            std::cout << "reset map: " << it.first << " -> "
//                      << "(" << (int)color.r << "," << (int)color.g << "," << (int)color.b << ")" << std::endl;
//        }

        std::cout << "clear" << std::endl;
        map.clear();
    }
}

void dbitmap::track_pixel(int id, rgb &color, const coords_t &coords) {
    if (id < dbit_cache.size()) {
        gridmap &cache = dbit_cache[id];

        size_t row = std::get<0>(coords);
        size_t col = std::get<1>(coords);
        std::string key = std::to_string(row) + "-" + std::to_string(col);

//        std::cout << "track pixel: " << id << ", (" << row << "," << col << ") -> " << key
//            << " rgb=(" << (int)color.r << "," << (int)color.g << "," << (int)color.b << ")" << std::endl;
        cache[key] = color;
    }
}

dbitmap::~dbitmap() {
    if (!dbit_cache.empty()) {
        dbit_cache.clear();
    }
}
