//
// Created by jimmy on 2020-11-30.
//

#include <cstdio>
#include <iostream>
#include <tuple>
#include <cassert>
#include "dbitmap.h"
#include "rgb.h"
#include "prog.h"

int dbitmap::mark() {
    auto it = dirty_cache.begin();
    for (int i = 0; it != dirty_cache.end(); ++it, ++i) {
        if ((*it).empty()) {
            return i;
        }
    }

    dirty_cache.emplace_back(dbit_cache());
    int id = (int)dirty_cache.size() - 1;
    return id;
}

void dbitmap::reset(int id) {
    if (id < dirty_cache.size()) {
        dbit_cache &stack_cache = dirty_cache[id];

        while (!stack_cache.empty()) {
            auto pair = stack_cache.top();
            set(pair.second, pair.first);

            stack_cache.pop();
        }

        // just to make sure
        assert(stack_cache.empty());
    }
}

dbitmap::~dbitmap() {
    if (!dirty_cache.empty()) {
        dirty_cache.clear();
    }
}

void dbitmap::save(int id, rgb &color, const coords_t &coords) {
    if (id < dirty_cache.size()) {
        dbit_cache &cache = dirty_cache[id];
        cache.push(std::make_pair(coords, color));
    }
}
