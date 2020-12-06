//
// Created by jimmy on 2020-12-03.
//

#include <sstream>
#include <string>

#include "tunnel.h"
#include "station.h"
#include "platform.h"
#include "spawn.h"

void station::link(entity *other) {
    {
        auto *ptr = dynamic_cast<station *>(other);
        if (ptr != nullptr) {
            warn_illegal_link(this, other);
            return;
        }
    }

    {
        auto *ptr = dynamic_cast<platform *>(other);
        if (ptr != nullptr) {
            platforms.push_back(ptr);
            return;
        }
    }

    {
        auto *ptr = dynamic_cast<tunnel *>(other);
        if (ptr != nullptr) {
            warn_illegal_link(this, other);
            return;
        }
    }

    {
        auto *ptr = dynamic_cast<spawn *>(other);
        if (ptr != nullptr) {
            spawns.push_back(ptr);
            return;
        }
    }
}

inline std::string station::name() {
    std::stringstream sstream;
    sstream << "station" << box.top_left().str();
    return sstream.str();
}
